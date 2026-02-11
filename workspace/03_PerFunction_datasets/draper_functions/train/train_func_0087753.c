dictAdd(dict *ht, void *key, void *val)
{
    int index;
    dictEntry *entry;


    if ((index = _dictKeyIndex(ht, key)) == -1)
        return DICT_ERR;


    entry = _dictAlloc(sizeof(*entry));
    entry->next = ht->table[index];
    ht->table[index] = entry;


    dictSetHashKey(ht, entry, key);
    dictSetHashVal(ht, entry, val);
    ht->used++;
    return DICT_OK;
}
