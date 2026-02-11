ompi_osc_rdma_component_irecv(void *buf,
                               size_t count,
                               struct ompi_datatype_t *datatype,
                               int src,
                               int tag,
                               struct ompi_communicator_t *comm,
                               ompi_request_t **request,
                               ompi_request_complete_fn_t callback,
                               void *cbdata)
{
    int ret;
    bool missed_callback;
    ompi_request_complete_fn_t tmp;

    ret = MCA_PML_CALL(irecv(buf, count, datatype,
                             src, tag, comm, request));
    if (OMPI_SUCCESS != ret) return ret;


    OPAL_THREAD_LOCK(&ompi_request_lock);
    (*request)->req_complete_cb = callback;
    (*request)->req_complete_cb_data = cbdata;
    missed_callback = (*request)->req_complete;
    OPAL_THREAD_UNLOCK(&ompi_request_lock);

    if (missed_callback) {
        tmp = (*request)->req_complete_cb;
        (*request)->req_complete_cb = NULL;
        tmp(*request);
    }

    return OMPI_SUCCESS;
}
