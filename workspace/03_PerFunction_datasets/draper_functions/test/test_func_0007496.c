Jim_ReplaceHashEntry(Jim_HashTable *ht, const void *key, void *val)
{
    int existed;
    Jim_HashEntry *entry;


    entry = JimInsertHashEntry(ht, key, 1);
    if (entry->key) {

        Jim_FreeEntryVal(ht, entry);
        existed = 1;
    }
    else {

        Jim_SetHashKey(ht, entry, key);
        existed = 0;
    }
    Jim_SetHashVal(ht, entry, val);

    return existed;
}
