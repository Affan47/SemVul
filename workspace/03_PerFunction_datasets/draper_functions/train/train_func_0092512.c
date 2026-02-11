remove_hash(Hashtable *ht, const void *key, size_t keylen)
{
    u_long val, slot;
    void *e, *laste = NULL;

    val = HASH_VALUE(key, keylen);
    slot = (val % ht->size);
    e = ht->slot[slot];
    while (e) {
       if ((*ht->testfn)(e, key)) {

           if (laste)
              HASH_NEXT(ht, laste) = HASH_NEXT(ht, e);
           else
              ht->slot[slot] = HASH_NEXT(ht, e);
           HASH_NEXT(ht, e) = NULL;
           return 1;
       }
       laste = e;
       e = HASH_NEXT(ht, e);
    }

    return 0;
}
