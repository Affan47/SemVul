mca_pml_bfo_process_pending_rdma(void)
{
    mca_pml_bfo_rdma_frag_t* frag;
    int32_t i, rc, s = (int32_t)opal_list_get_size(&mca_pml_bfo.rdma_pending);

    for(i = 0; i < s; i++) {
        OPAL_THREAD_LOCK(&mca_pml_bfo.lock);
        frag = (mca_pml_bfo_rdma_frag_t*)
            opal_list_remove_first(&mca_pml_bfo.rdma_pending);
        OPAL_THREAD_UNLOCK(&mca_pml_bfo.lock);
        if(NULL == frag)
            break;
        if(frag->rdma_state == MCA_PML_BFO_RDMA_PUT) {
            frag->retries++;
            rc = mca_pml_bfo_send_request_put_frag(frag);
        } else {
            rc = mca_pml_bfo_recv_request_get_frag(frag);
        }
        if(OMPI_ERR_OUT_OF_RESOURCE == rc)
            break;
    }
}
