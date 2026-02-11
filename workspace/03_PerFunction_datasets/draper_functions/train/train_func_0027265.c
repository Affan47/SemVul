mca_pml_bfo_recv_request_ack(
    mca_pml_bfo_recv_request_t* recvreq,
    mca_pml_bfo_rendezvous_hdr_t* hdr,
    size_t bytes_received)
{
    ompi_proc_t* proc = (ompi_proc_t*)recvreq->req_recv.req_base.req_proc;
    mca_bml_base_endpoint_t* bml_endpoint = NULL;

    bml_endpoint = (mca_bml_base_endpoint_t*) proc->proc_endpoints[OMPI_PROC_ENDPOINT_TAG_BML];


    recvreq->req_send_offset = bytes_received;
    if(hdr->hdr_msg_length > bytes_received) {
        size_t rdma_num = mca_bml_base_btl_array_get_size(&bml_endpoint->btl_rdma);


        if(opal_convertor_need_buffers(&recvreq->req_recv.req_base.req_convertor) == 0 &&
           hdr->hdr_match.hdr_common.hdr_flags & MCA_PML_BFO_HDR_FLAGS_CONTIG &&
           rdma_num != 0) {
            unsigned char *base;
            opal_convertor_get_current_pointer( &recvreq->req_recv.req_base.req_convertor, (void**)&(base) );

            if(hdr->hdr_match.hdr_common.hdr_flags & MCA_PML_BFO_HDR_FLAGS_PIN)
                recvreq->req_rdma_cnt = mca_pml_bfo_rdma_btls(bml_endpoint,
                        base, recvreq->req_recv.req_bytes_packed,
                        recvreq->req_rdma );
            else
                recvreq->req_rdma_cnt = 0;


            if (recvreq->req_rdma_cnt != 0) {
                recvreq->req_send_offset = hdr->hdr_msg_length;

            } else if(bml_endpoint->btl_send_limit < hdr->hdr_msg_length) {

                recvreq->req_send_offset = hdr->hdr_msg_length -
                    bml_endpoint->btl_pipeline_send_length;

                if(recvreq->req_send_offset < bytes_received)
                    recvreq->req_send_offset = bytes_received;


                opal_convertor_set_position(&recvreq->req_recv.req_base.req_convertor,
                        &recvreq->req_send_offset);

                recvreq->req_rdma_cnt =
                    mca_pml_bfo_rdma_pipeline_btls(bml_endpoint,
                            recvreq->req_send_offset - bytes_received,
                            recvreq->req_rdma);
            }
        }

        if(recvreq->req_send_offset == hdr->hdr_msg_length)
            return OMPI_SUCCESS;
    }

    recvreq->req_ack_sent = true;
    return mca_pml_bfo_recv_request_ack_send(proc, hdr->hdr_src_req.lval,
                                             recvreq, recvreq->req_send_offset,
                                             recvreq->req_send_offset == bytes_received);
}
