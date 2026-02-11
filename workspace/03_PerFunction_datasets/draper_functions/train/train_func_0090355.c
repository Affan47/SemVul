cmpd_each(Store *store,
                     void (*func)(char *fname, void *arg), void *arg)
{
    HashTable *ht = store->dir.cmpd->entries;
    int i;
    for (i = 0; i <= ht->mask; i++) {
        char *fn = (char *)ht->table[i].key;
        if (fn) {
            func(fn, arg);
        }
    }
}
