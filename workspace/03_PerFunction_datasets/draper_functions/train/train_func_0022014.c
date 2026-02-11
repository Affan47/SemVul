mca_memheap_base_get_cached_mkey(int pe,
                                                   void* va,
                                                   int btl_id,
                                                   void** rva)
{
    map_segment_t *s;
    int rc;
    mca_spml_mkey_t *mkey;

    MEMHEAP_VERBOSE_FASTPATH(10, "rkey: pe=%d va=%p", pe, va);
    s = __find_va(va);
    if (NULL == s)
        return NULL ;

    if (!s->is_active)
        return NULL ;

    if (pe == oshmem_my_proc_id()) {
        *rva = va;
        MEMHEAP_VERBOSE_FASTPATH(10, "rkey: pe=%d va=%p -> (local) %lx %p", pe, va,
                s->mkeys[btl_id].key, *rva);
        return &s->mkeys[btl_id];
    }

    if (OPAL_LIKELY(s->mkeys_cache[pe])) {
        mkey = &s->mkeys_cache[pe][btl_id];
        *rva = va2rva(va, s->start, mkey->va_base);
        MEMHEAP_VERBOSE_FASTPATH(10, "rkey: pe=%d va=%p -> (cached) %lx %p", pe, (void *)va, mkey->key, (void *)*rva);
        return mkey;
    }

    s->mkeys_cache[pe] = (mca_spml_mkey_t *) calloc(memheap_map->num_transports,
                                                    sizeof(mca_spml_mkey_t));
    if (!s->mkeys_cache[pe])
        return NULL ;

    rc = memheap_oob_get_mkeys(pe,
                               s - memheap_map->mem_segs,
                               s->mkeys_cache[pe]);
    if (OSHMEM_SUCCESS != rc)
        return NULL ;

    mkey = &s->mkeys_cache[pe][btl_id];
    *rva = va2rva(va, s->start, mkey->va_base);

    MEMHEAP_VERBOSE_FASTPATH(5, "rkey: pe=%d va=%p -> (remote lookup) %lx %p", pe, (void *)va, mkey->key, (void *)*rva);
    return mkey;
}
