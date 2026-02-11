mca_pml_ob1_send_request_put( mca_pml_ob1_send_request_t* sendreq,
                                   mca_btl_base_module_t* btl,
                                   mca_pml_ob1_rdma_hdr_t* hdr )
{
    mca_bml_base_endpoint_t *bml_endpoint = sendreq->req_endpoint;
    mca_pml_ob1_rdma_frag_t* frag;
    size_t i, size = 0;

    if(hdr->hdr_common.hdr_flags & MCA_PML_OB1_HDR_TYPE_ACK) {
        OPAL_THREAD_ADD32(&sendreq->req_state, -1);
    }

    sendreq->req_recv.pval = hdr->hdr_recv_req.pval;

    MCA_PML_OB1_RDMA_FRAG_ALLOC(frag);

    if( OPAL_UNLIKELY(NULL == frag) ) {

        OMPI_ERROR_LOG(OMPI_ERR_OUT_OF_RESOURCE);
        ompi_rte_abort(-1, NULL);
    }

    assert (btl->btl_seg_size * hdr->hdr_seg_cnt <= sizeof (frag->rdma_segs));


    memcpy (frag->rdma_segs, hdr + 1, btl->btl_seg_size * hdr->hdr_seg_cnt);

    for( i = 0; i < hdr->hdr_seg_cnt; i++ ) {
        mca_btl_base_segment_t *seg = (mca_btl_base_segment_t *) ((uintptr_t)(frag->rdma_segs) + i * btl->btl_seg_size);

#if OPAL_ENABLE_HETEROGENEOUS_SUPPORT
        if ((sendreq->req_send.req_base.req_proc->proc_arch & OPAL_ARCH_ISBIGENDIAN) !=
            (ompi_proc_local()->proc_arch & OPAL_ARCH_ISBIGENDIAN)) {
            size += opal_swap_bytes4(seg->seg_len);
        } else
#endif
        {
            size += seg->seg_len;
        }
    }

    frag->rdma_bml = mca_bml_base_btl_array_find(&bml_endpoint->btl_rdma, btl);
    frag->rdma_hdr.hdr_rdma = *hdr;
    frag->rdma_req = sendreq;
    frag->rdma_ep = bml_endpoint;
    frag->rdma_length = size;
    frag->rdma_state = MCA_PML_OB1_RDMA_PUT;
    frag->reg = NULL;
    frag->retries = 0;

    if (OPAL_UNLIKELY(NULL != sendreq->src_des)) {

        sendreq->req_state = 0;
    }


    for(i=0; i<sendreq->req_rdma_cnt; i++) {
        if(sendreq->req_rdma[i].bml_btl == frag->rdma_bml) {
            frag->reg = sendreq->req_rdma[i].btl_reg;
            break;
        }
    }


    size = hdr->hdr_rdma_offset;
    opal_convertor_clone_with_position(&sendreq->req_send.req_base.req_convertor,
                                       &frag->convertor, 0, &size);

    mca_pml_ob1_send_request_put_frag(frag);
}
