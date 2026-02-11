mca_pml_bfo_update_eager_bml_btl_recv_ctl(mca_bml_base_btl_t** bml_btl,
                                               mca_btl_base_module_t* btl,
                                               struct mca_btl_base_descriptor_t* des)
{
    if ((*bml_btl)->btl != btl) {
        mca_pml_bfo_common_hdr_t * common = des->des_src->seg_addr.pval;
        mca_pml_bfo_ack_hdr_t* ack;
        mca_pml_bfo_recv_request_t* recvreq = NULL;
        char *type = NULL;

        switch (common->hdr_type) {
        case MCA_PML_BFO_HDR_TYPE_ACK:
            ack = (mca_pml_bfo_ack_hdr_t*)des->des_src->seg_addr.pval;
            recvreq = (mca_pml_bfo_recv_request_t*) ack->hdr_dst_req.pval;
            type = "ACK";
            break;
        case MCA_PML_BFO_HDR_TYPE_PUT:
            recvreq = des->des_cbdata;
            type = "PUT";
            break;
        default:

            opal_output(0, "%s:%d FATAL ERROR, unknown header (hdr=%d)",
                        __FILE__, __LINE__, common->hdr_type);
            ompi_rte_abort(-1, NULL);
        }

        mca_pml_bfo_find_recvreq_eager_bml_btl(bml_btl, btl, recvreq, type);
    }
}
