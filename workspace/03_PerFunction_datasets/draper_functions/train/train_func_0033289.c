mca_pml_bfo_put_completion( mca_btl_base_module_t* btl,
                                        struct mca_btl_base_endpoint_t* ep,
                                        struct mca_btl_base_descriptor_t* des,
                                        int status )
{
    mca_pml_bfo_rdma_frag_t* frag = (mca_pml_bfo_rdma_frag_t*)des->des_cbdata;
    mca_pml_bfo_send_request_t* sendreq = (mca_pml_bfo_send_request_t*)frag->rdma_req;
    mca_bml_base_btl_t* bml_btl = (mca_bml_base_btl_t*) des->des_context;


    if( OPAL_UNLIKELY(OMPI_SUCCESS != status) ) {
#if PML_BFO
        sendreq->req_error++;
#else

        OMPI_ERROR_LOG(status);
        ompi_rte_abort(-1, NULL);
#endif
    }
#if PML_BFO
    sendreq->req_events--;
    MCA_PML_BFO_PUT_COMPLETION_SENDREQ_ERROR_CHECK(sendreq, status, btl);
    MCA_PML_BFO_CHECK_SENDREQ_EAGER_BML_BTL(bml_btl, btl, sendreq, "RDMA write");
#endif

    mca_pml_bfo_send_fin(sendreq->req_send.req_base.req_proc,
                         bml_btl,
                         frag->rdma_hdr.hdr_rdma.hdr_des,
#if PML_BFO
                         des->order, 0, (uint16_t)sendreq->req_send.req_base.req_sequence,
                         sendreq->req_restartseq, sendreq->req_send.req_base.req_comm->c_contextid,
                         sendreq->req_send.req_base.req_comm->c_my_rank);
#else
                         des->order, 0);
#endif


    OPAL_THREAD_ADD_SIZE_T(&sendreq->req_bytes_delivered, frag->rdma_length);

    send_request_pml_complete_check(sendreq);

    MCA_PML_BFO_RDMA_FRAG_RETURN(frag);

    MCA_PML_BFO_PROGRESS_PENDING(bml_btl);
}
