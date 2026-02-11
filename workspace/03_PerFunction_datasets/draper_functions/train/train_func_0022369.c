JS_HashTableRawLookup(JSHashTable *ht, JSHashNumber keyHash, const void *key)
{
    JSHashEntry *he, **hep, **hep0;

#ifdef JS_HASHMETER
    ht->nlookups++;
#endif
    hep = hep0 = BUCKET_HEAD(ht, keyHash);
    while ((he = *hep) != NULL) {
        if (he->keyHash == keyHash && ht->keyCompare(key, he->key)) {

            if (hep != hep0) {
                *hep = he->next;
                he->next = *hep0;
                *hep0 = he;
            }
            return hep0;
        }
        hep = &he->next;
#ifdef JS_HASHMETER
        ht->nsteps++;
#endif
    }
    return hep;
}
