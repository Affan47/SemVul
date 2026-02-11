mca_btl_self_prepare_dst( struct mca_btl_base_module_t* btl,
                          struct mca_btl_base_endpoint_t* endpoint,
                          mca_mpool_base_registration_t* registration,
                          struct opal_convertor_t* convertor,
                          uint8_t order,
                          size_t reserve,
                          size_t* size,
                          uint32_t flags )
{
    mca_btl_self_frag_t* frag;
    size_t max_data = *size;
    void *ptr;

    MCA_BTL_SELF_FRAG_ALLOC_RDMA(frag);
    if(OPAL_UNLIKELY(NULL == frag)) {
        return NULL;
    }


    opal_convertor_get_current_pointer( convertor, &ptr );
    frag->segment.seg_addr.lval = (uint64_t)(uintptr_t) ptr;

    frag->segment.seg_len = reserve + max_data;
    frag->base.des_dst = &frag->segment;
    frag->base.des_dst_cnt = 1;
    frag->base.des_flags = flags;
    return &frag->base;
}
