ompi_osc_rdma_sendreq_send_long_cb(ompi_request_t *request)
{
    ompi_osc_rdma_longreq_t *longreq =
        (ompi_osc_rdma_longreq_t*) request->req_complete_cb_data;
    ompi_osc_rdma_sendreq_t *sendreq = longreq->req_basereq.req_sendreq;
    int32_t count;

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "%d completed long sendreq to %d",
                         ompi_comm_rank(sendreq->req_module->m_comm),
                         sendreq->req_target_rank));

    OPAL_THREAD_LOCK(&sendreq->req_module->m_lock);
    count = (sendreq->req_module->m_num_pending_out -= 1);
    OPAL_THREAD_UNLOCK(&sendreq->req_module->m_lock);

    ompi_osc_rdma_longreq_free(longreq);
    ompi_osc_rdma_sendreq_free(sendreq);

    if (0 == count) opal_condition_broadcast(&sendreq->req_module->m_cond);

    ompi_request_free(&request);
    return OMPI_SUCCESS;
}
