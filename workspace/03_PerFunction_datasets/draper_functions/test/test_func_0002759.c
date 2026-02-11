mca_btl_sctp_put(
    mca_btl_base_module_t* btl,
    mca_btl_base_endpoint_t* endpoint,
    mca_btl_base_descriptor_t* descriptor)
{
    mca_btl_sctp_module_t* sctp_btl = (mca_btl_sctp_module_t*) btl;
    mca_btl_sctp_frag_t* frag = (mca_btl_sctp_frag_t*)descriptor;
    size_t i;

    frag->btl = sctp_btl;
    frag->endpoint = endpoint;
    frag->rc = 0;
    frag->iov_idx = 0;
    frag->hdr.size = 0;
    frag->iov_cnt = 2;
    frag->iov_ptr = frag->iov;
    frag->iov[0].iov_base = (IOVBASE_TYPE*)&frag->hdr;
    frag->iov[0].iov_len = sizeof(frag->hdr);
    frag->iov[1].iov_base = (IOVBASE_TYPE*)frag->base.des_dst;
    frag->iov[1].iov_len = frag->base.des_dst_cnt * sizeof(mca_btl_base_segment_t);
    for(i=0; i<frag->base.des_src_cnt; i++) {
        frag->hdr.size += frag->segments[i].seg_len;
        frag->iov[i+2].iov_len = frag->segments[i].seg_len;
        frag->iov[i+2].iov_base = (IOVBASE_TYPE*)frag->segments[i].seg_addr.pval;
        frag->iov_cnt++;
    }
    frag->hdr.base.tag = MCA_BTL_TAG_BTL;
    frag->hdr.type = MCA_BTL_SCTP_HDR_TYPE_PUT;
    frag->hdr.count = frag->base.des_dst_cnt;
    if (endpoint->endpoint_nbo) {
        MCA_BTL_SCTP_HDR_HTON(frag->hdr);
    }
    return mca_btl_sctp_endpoint_send(endpoint,frag);
}
