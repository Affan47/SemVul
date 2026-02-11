mca_mpool_sm_alloc(
    mca_mpool_base_module_t* mpool,
    size_t size,
    size_t align,
    uint32_t flags,
    mca_mpool_base_registration_t** registration)
{
    mca_mpool_sm_module_t* mpool_sm = (mca_mpool_sm_module_t*)mpool;
    opal_hwloc_base_memory_segment_t mseg;

    mseg.mbs_start_addr =
        mpool_sm->sm_allocator->alc_alloc(mpool_sm->sm_allocator, size, align, registration);

    if(mpool_sm->mem_node >= 0) {
        mseg.mbs_len = size;
#if OPAL_HAVE_HWLOC
        opal_hwloc_base_membind(&mseg, 1, mpool_sm->mem_node);
#endif
    }

#if OPAL_CUDA_SUPPORT
    if (flags & MCA_MPOOL_FLAGS_CUDA_REGISTER_MEM) {
        mca_common_cuda_register(mseg.mbs_start_addr, size,
                                 mpool->mpool_component->mpool_version.mca_component_name);
    }
#endif

    return mseg.mbs_start_addr;
}
