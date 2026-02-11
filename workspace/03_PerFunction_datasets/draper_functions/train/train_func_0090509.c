vader_prepare_dst(struct mca_btl_base_module_t *btl,
                                                    struct mca_btl_base_endpoint_t *endpoint,
                                                    struct mca_mpool_base_registration_t *registration,
                                                    struct opal_convertor_t *convertor,
                                                    uint8_t order, size_t reserve, size_t *size,
                                                    uint32_t flags)
{
    mca_btl_vader_frag_t *frag;
    void *data_ptr;

    (void) MCA_BTL_VADER_FRAG_ALLOC_USER(frag, endpoint);
    if (OPAL_UNLIKELY(NULL == frag)) {
        return NULL;
    }

    opal_convertor_get_current_pointer (convertor, &data_ptr);

    frag->segments[0].seg_addr.lval = (uint64_t)(uintptr_t) data_ptr;
    frag->segments[0].seg_len       = *size;

    frag->base.order       = order;
    frag->base.des_flags   = flags;

    return &frag->base;
}
