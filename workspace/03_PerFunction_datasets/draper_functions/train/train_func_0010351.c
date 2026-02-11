get(hashtable *ht, const char * key) {

    int bin = hash(key) % ht->size;
    entry *curr = ht->table[bin];


    while (NULL != curr && 0 != strcmp(curr->key, key)) {
        curr = curr->next;
    }


    if (curr == NULL) {
        return NULL;
    }

    return curr->value;

}
