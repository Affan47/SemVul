mca_btl_openib_endpoint_credits(
    mca_btl_base_module_t* btl,
    struct mca_btl_base_endpoint_t* ep,
    struct mca_btl_base_descriptor_t* des,
    int status)
{

    int qp;

    mca_btl_openib_send_control_frag_t *frag = to_send_control_frag(des);

    qp = frag->qp_idx;


    qp_get_wqe(ep, des->order);

    if(check_send_credits(ep, qp) || check_eager_rdma_credits(ep))
        mca_btl_openib_endpoint_send_credits(ep, qp);
    else {
        BTL_OPENIB_CREDITS_SEND_UNLOCK(ep, qp);

        send_credits(ep, qp);
    }
}
