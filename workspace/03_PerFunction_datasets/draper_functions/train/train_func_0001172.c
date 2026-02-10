_reg_segment(map_segment_t *s, int *num_btl)
{
    int rc = OSHMEM_SUCCESS;
    int my_pe;
    int nprocs;

    nprocs = oshmem_num_procs();
    my_pe = oshmem_my_proc_id();

    s->mkeys_cache = (sshmem_mkey_t **) calloc(nprocs,
                                                 sizeof(sshmem_mkey_t *));
    if (NULL == s->mkeys_cache) {
        MEMHEAP_ERROR("Failed to allocate memory for remote segments");
        rc = OSHMEM_ERROR;
    }

    if (!rc) {
        s->mkeys = MCA_SPML_CALL(register((void *)(unsigned long)s->seg_base_addr,
                        (uintptr_t)s->end - (uintptr_t)s->seg_base_addr,
                        s->seg_id,
                        num_btl));
        if (NULL == s->mkeys) {
            free(s->mkeys_cache);
            s->mkeys_cache = NULL;

            MEMHEAP_ERROR("Failed to register segment");
            rc = OSHMEM_ERROR;
        }
    }

    if (OSHMEM_SUCCESS == rc) {
        s->mkeys_cache[my_pe] = s->mkeys;
        MAP_SEGMENT_SET_VALID(s);
    }

    return rc;
}
