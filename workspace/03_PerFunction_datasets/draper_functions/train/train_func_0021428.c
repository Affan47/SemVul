_dictKeyIndex(dict *ht, const void *key)
{
    unsigned int h;
    dictEntry *he;


    if (_dictExpandIfNeeded(ht) == DICT_ERR)
        return -1;

    h = dictHashKey(ht, key) & ht->sizemask;

    he = ht->table[h];
    while(he) {
        if (dictCompareHashKeys(ht, key, he->key))
            return -1;
        he = he->next;
    }
    return h;
}
