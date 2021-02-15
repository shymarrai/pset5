// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//size of dictionary
unsigned int dictionary_size = 0;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *list = table[hash(word)];
    for (node *n = list; n != NULL; n = n->next)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return tolower(word[0]) % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);

    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //printf("word loaded: %s\n", word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not alocate memory.\n");
            return false;
        }

        strcpy(n->word, word);

        unsigned  word_position = hash(word);
        n->next = table[word_position];
        table[word_position] = n;


        dictionary_size++;

    }
    if (ferror(file))
    {
        printf("Error reading %s. \n", dictionary);
        return false;
    }

    fclose(file);

    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }

    }
    return true;
}
