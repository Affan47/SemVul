item_alloc(char *key, int flags, time_t exptime, int nbytes) {
    int ntotal, len;
    item *it;
    unsigned int id;

    len = strlen(key) + 1; if(len % 4) len += 4 - (len % 4);
    ntotal = sizeof(item) + len + nbytes;

    id = slabs_clsid(ntotal);
    if (id == 0)
        return 0;

    it = slabs_alloc(ntotal);
    if (it == 0) {
        int tries = 50;
        item *search;


        if (!settings.evict_to_free) return 0;


        if (id > LARGEST_ID) return 0;
        if (tails[id]==0) return 0;

        for (search = tails[id]; tries>0 && search; tries--, search=search->prev) {
            if (search->refcount==0) {
                item_unlink(search);
                break;
            }
        }
        it = slabs_alloc(ntotal);
        if (it==0) return 0;
    }

    assert(it->slabs_clsid == 0);

    it->slabs_clsid = id;

    assert(it != heads[it->slabs_clsid]);

    it->next = it->prev = it->h_next = 0;
    it->refcount = 0;
    it->it_flags = 0;
    it->nkey = len;
    it->nbytes = nbytes;
    strcpy(ITEM_key(it), key);
    it->exptime = exptime;
    it->flags = flags;
    return it;
}
