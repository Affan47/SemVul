create_hashtable(unsigned int minsize,
                 unsigned int (*hashf) (void*),
                 int (*compf) (void*,void*),
		 void (*destroyf) (void *))
{
    struct hashtable *h;
    unsigned int pindex, size = primes[0];

    if (minsize > (1u << 30)) return NULL;

    for (pindex=0; pindex < prime_table_length; pindex++) {
        if (primes[pindex] > minsize) { size = primes[pindex]; break; }
    }
    h = (struct hashtable *)malloc(sizeof(struct hashtable));
    if (NULL == h) return NULL;
    h->table = (struct entry **)malloc(sizeof(struct entry*) * size);
    if (NULL == h->table) { free(h); return NULL; }
    memset(h->table, 0, size * sizeof(struct entry *));
    h->tablelength  = size;
    h->primeindex   = pindex;
    h->entrycount   = 0;
    h->hashfn       = hashf;
    h->compfn         = compf;
    h->destroyfn    = destroyf ? destroyf : free;
    h->loadlimit    = (unsigned int) ceil(size * max_load_factor);
    return h;
}
