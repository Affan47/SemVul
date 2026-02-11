append_recv_req_to_queue(opal_list_t *queue,
        mca_pml_ob1_recv_request_t *req)
{
    if(OPAL_UNLIKELY(req->req_recv.req_base.req_type == MCA_PML_REQUEST_IPROBE ||
                     req->req_recv.req_base.req_type == MCA_PML_REQUEST_IMPROBE))
        return;

    opal_list_append(queue, (opal_list_item_t*)req);


    if(req->req_recv.req_base.req_type != MCA_PML_REQUEST_PROBE ||
       req->req_recv.req_base.req_type != MCA_PML_REQUEST_MPROBE) {
        PERUSE_TRACE_COMM_EVENT(PERUSE_COMM_REQ_INSERT_IN_POSTED_Q,
                                &(req->req_recv.req_base), PERUSE_RECV);
    }
}
