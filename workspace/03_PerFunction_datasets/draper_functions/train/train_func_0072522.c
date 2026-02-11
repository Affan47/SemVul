Resize(JSHashTable *ht, uint32 newshift)
{
    size_t nb, nentries, i;
    JSHashEntry **oldbuckets, *he, *next, **hep;
    size_t nold = NBUCKETS(ht);

    JS_ASSERT(newshift < JS_HASH_BITS);

    nb = (size_t)1 << (JS_HASH_BITS - newshift);


    if (nb > (size_t)-1 / sizeof(JSHashEntry*))
        return JS_FALSE;
    nb *= sizeof(JSHashEntry*);

    oldbuckets = ht->buckets;
    ht->buckets = (JSHashEntry**)ht->allocOps->allocTable(ht->allocPriv, nb);
    if (!ht->buckets) {
        ht->buckets = oldbuckets;
        return JS_FALSE;
    }
    memset(ht->buckets, 0, nb);

    ht->shift = newshift;
    nentries = ht->nentries;

    for (i = 0; nentries != 0; i++) {
        for (he = oldbuckets[i]; he; he = next) {
            JS_ASSERT(nentries != 0);
            --nentries;
            next = he->next;
            hep = BUCKET_HEAD(ht, he->keyHash);


            while (*hep)
                hep = &(*hep)->next;
            he->next = NULL;
            *hep = he;
        }
    }
#ifdef DEBUG
    memset(oldbuckets, 0xDB, nold * sizeof oldbuckets[0]);
#endif
    ht->allocOps->freeTable(ht->allocPriv, oldbuckets,
                            nold * sizeof oldbuckets[0]);
    return JS_TRUE;
}
