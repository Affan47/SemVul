do_slabs_alloc(const size_t size, unsigned int id) {
    slabclass_t *p;
    void *ret = NULL;

    if (id < POWER_SMALLEST || id > power_largest) {
        MEMCACHED_SLABS_ALLOCATE_FAILED(size, 0);
        return NULL;
    }

    p = &slabclass[id];
    assert(p->sl_curr == 0 || ((item *)p->slots[p->sl_curr - 1])->slabs_clsid == 0);

#ifdef USE_SYSTEM_MALLOC
    if (mem_limit && mem_malloced + size > mem_limit) {
        MEMCACHED_SLABS_ALLOCATE_FAILED(size, id);
        return 0;
    }
    mem_malloced += size;
    ret = malloc(size);
    MEMCACHED_SLABS_ALLOCATE(size, id, 0, ret);
    return ret;
#endif


    if (! (p->end_page_ptr != 0 || p->sl_curr != 0 ||
           do_slabs_newslab(id) != 0)) {

        ret = NULL;
    } else if (p->sl_curr != 0) {

        ret = p->slots[--p->sl_curr];
    } else {

        assert(p->end_page_ptr != NULL);
        ret = p->end_page_ptr;
        if (--p->end_page_free != 0) {
            p->end_page_ptr += p->size;
        } else {
            p->end_page_ptr = 0;
        }
    }

    if (ret) {
        MEMCACHED_SLABS_ALLOCATE(size, id, p->size, ret);
    } else {
        MEMCACHED_SLABS_ALLOCATE_FAILED(size, id);
    }

    return ret;
}
