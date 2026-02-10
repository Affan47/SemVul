mca_pml_bfo_send_request_put_frag( mca_pml_bfo_rdma_frag_t* frag )
{
    mca_mpool_base_registration_t* reg = NULL;
    mca_bml_base_btl_t* bml_btl = frag->rdma_bml;
    mca_btl_base_descriptor_t* des;
    size_t save_size = frag->rdma_length;
    int rc;


    mca_bml_base_prepare_src( bml_btl,
                              reg,
                              &frag->convertor,
                              MCA_BTL_NO_ORDER,
                              0,
                              &frag->rdma_length,
                              MCA_BTL_DES_FLAGS_BTL_OWNERSHIP |
                              MCA_BTL_DES_FLAGS_PUT,
                              &des );

    if( OPAL_UNLIKELY(NULL == des) ) {
        if(frag->retries < mca_pml_bfo.rdma_put_retries_limit) {
            size_t offset = (size_t)frag->rdma_hdr.hdr_rdma.hdr_rdma_offset;
            frag->rdma_length = save_size;
            opal_convertor_set_position(&frag->convertor, &offset);
            OPAL_THREAD_LOCK(&mca_pml_bfo.lock);
            opal_list_append(&mca_pml_bfo.rdma_pending, (opal_list_item_t*)frag);
            OPAL_THREAD_UNLOCK(&mca_pml_bfo.lock);
        } else {
            mca_pml_bfo_send_request_t *sendreq =
                (mca_pml_bfo_send_request_t*)frag->rdma_req;


            mca_pml_bfo_send_fin(sendreq->req_send.req_base.req_proc,
                    bml_btl, frag->rdma_hdr.hdr_rdma.hdr_des,
#if PML_BFO
                    MCA_BTL_NO_ORDER, 1, (uint16_t)sendreq->req_send.req_base.req_sequence,
                    sendreq->req_restartseq, sendreq->req_send.req_base.req_comm->c_contextid,
                    sendreq->req_send.req_base.req_comm->c_my_rank);
#else
                    MCA_BTL_NO_ORDER, 1);
#endif


            mca_pml_bfo_send_request_copy_in_out(sendreq,
                    frag->rdma_hdr.hdr_rdma.hdr_rdma_offset, frag->rdma_length);


            if(NULL != sendreq->req_recv.pval)
                mca_pml_bfo_send_request_schedule(sendreq);
        }
        return OMPI_ERR_OUT_OF_RESOURCE;
    }

    des->des_dst = (mca_btl_base_segment_t *) frag->rdma_segs;
    des->des_dst_cnt = frag->rdma_hdr.hdr_rdma.hdr_seg_cnt;
    des->des_cbfunc = mca_pml_bfo_put_completion;
    des->des_cbdata = frag;

    PERUSE_TRACE_COMM_OMPI_EVENT( PERUSE_COMM_REQ_XFER_CONTINUE,
                                  &(((mca_pml_bfo_send_request_t*)frag->rdma_req)->req_send.req_base), save_size, PERUSE_SEND );

    rc = mca_bml_base_put(bml_btl, des);
    if( OPAL_UNLIKELY(OMPI_SUCCESS != rc) ) {
        mca_bml_base_free(bml_btl, des);
        frag->rdma_length = save_size;
        if(OMPI_ERR_OUT_OF_RESOURCE == rc) {
            OPAL_THREAD_LOCK(&mca_pml_bfo.lock);
            opal_list_append(&mca_pml_bfo.rdma_pending, (opal_list_item_t*)frag);
            OPAL_THREAD_UNLOCK(&mca_pml_bfo.lock);
            return OMPI_ERR_OUT_OF_RESOURCE;
        } else {

            OMPI_ERROR_LOG(rc);
            ompi_rte_abort(-1, NULL);
        }
    }
#if PML_BFO
    if (des->des_flags & MCA_BTL_DES_SEND_ALWAYS_CALLBACK) {
        ((mca_pml_bfo_send_request_t*)frag->rdma_req)->req_events++;
    }
#endif
    return OMPI_SUCCESS;
}
