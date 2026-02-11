ht_init_f(hashtable **ht, hash_t (*hashfunc)(const void*, const void*),
        int (*cmpfunc)(const void*, const void*, const void*),
        void (*free_key)(void*), void (*free_data)(void*))
{
    hashtable *p;


    if (!hashfunc && !cmpfunc)
    {
        hashfunc = ht_strhash;
        cmpfunc = ht_strcmp;
    }

    else if (!hashfunc || !cmpfunc)
    {
        *ht = NULL;
        return HT_ERROR;
    }

    p = malloc(sizeof *p);

    if (!p)
    {
        *ht = NULL;
        return HT_ERROR;
    }

    srand(time(NULL));

    p->n_items = 0;
    p->n_buckets = PRIME(0);
    p->pgroup = 0;

    p->hash = hashfunc;
    p->cmp = cmpfunc;

    p->free_key = free_key;
    p->free_data = free_data;

    p->buckets = ht_alloc_buckets(p->n_buckets);

    if (!p->buckets)
    {
        free(p);
        *ht = NULL;
        return HT_ERROR;
    }

    *ht = p;
    return HT_OK;
}
