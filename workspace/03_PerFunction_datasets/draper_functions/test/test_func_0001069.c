mca_mpool_sm_realloc(
    mca_mpool_base_module_t* mpool,
    void* addr,
    size_t size,
    mca_mpool_base_registration_t** registration)
{
    mca_mpool_sm_module_t* mpool_sm = (mca_mpool_sm_module_t*)mpool;
    opal_hwloc_base_memory_segment_t mseg;

    mseg.mbs_start_addr =
        mpool_sm->sm_allocator->alc_realloc(mpool_sm->sm_allocator, addr, size,
                                            registration);
    if(mpool_sm->mem_node >= 0) {
        mseg.mbs_len = size;
#if OPAL_HAVE_HWLOC
        opal_hwloc_base_membind(&mseg, 1, mpool_sm->mem_node);
#endif
    }

    return mseg.mbs_start_addr;
}
