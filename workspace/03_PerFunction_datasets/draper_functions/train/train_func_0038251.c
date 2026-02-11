dictAdd(dict *d, void *key, void *val)
{
    int index;
    dictEntry *entry;
    dictht *ht;

    if (dictIsRehashing(d)) _dictRehashStep(d);


    if ((index = _dictKeyIndex(d, key)) == -1)
        return DICT_ERR;


    ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
    entry = zmalloc(sizeof(*entry));
    entry->next = ht->table[index];
    ht->table[index] = entry;
    ht->used++;


    dictSetHashKey(d, entry, key);
    dictSetHashVal(d, entry, val);
    return DICT_OK;
}
