mca_btl_vader_sendi (struct mca_btl_base_module_t *btl,
                         struct mca_btl_base_endpoint_t *endpoint,
                         struct opal_convertor_t *convertor,
                         void *header, size_t header_size,
                         size_t payload_size, uint8_t order,
                         uint32_t flags, mca_btl_base_tag_t tag,
                         mca_btl_base_descriptor_t **descriptor)
{
    mca_btl_vader_frag_t *frag;
    void *data_ptr = NULL;
    size_t length;

    if (payload_size) {
        opal_convertor_get_current_pointer (convertor, &data_ptr);
    }

    if (!(payload_size && opal_convertor_need_buffers (convertor)) &&
        mca_btl_vader_fbox_sendi (endpoint, tag, header, header_size, data_ptr, payload_size)) {
        return OMPI_SUCCESS;
    }


    length = header_size + payload_size;


    frag = (mca_btl_vader_frag_t *) mca_btl_vader_alloc (btl, endpoint, order, length,
                                                         flags | MCA_BTL_DES_FLAGS_BTL_OWNERSHIP);
    if (OPAL_UNLIKELY(NULL == frag)) {
        *descriptor = NULL;

        return OMPI_ERR_OUT_OF_RESOURCE;
    }


    frag->hdr->len = length;
    frag->hdr->tag = tag;


    memcpy (frag->segments[0].seg_addr.pval, header, header_size);


    if (payload_size) {
        uint32_t iov_count = 1;
        struct iovec iov;


        iov.iov_base = (IOVBASE_TYPE *)((uintptr_t)frag->segments[0].seg_addr.pval + header_size);
        iov.iov_len  = length = payload_size;

        (void) opal_convertor_pack (convertor, &iov, &iov_count, &length);

        assert (length == payload_size);
    }


    vader_fifo_write_ep (frag->hdr, endpoint);

    return OMPI_SUCCESS;
}
