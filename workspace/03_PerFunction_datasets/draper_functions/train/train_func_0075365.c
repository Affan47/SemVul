ompi_osc_rdma_isend_w_cb (void *ptr, int count, ompi_datatype_t *datatype, int target, int tag,
                              ompi_communicator_t *comm, ompi_request_complete_fn_t cb, void *ctx)
{
    ompi_request_t *request;
    int ret;

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "osc rdma: ompi_osc_rdma_isend_w_cb sending %d bytes to %d with tag %d",
                         count, target, tag));

    ret = MCA_PML_CALL(isend_init(ptr, count, datatype, target, tag,
                                  MCA_PML_BASE_SEND_STANDARD, comm, &request));
    if (OMPI_SUCCESS != ret) {
        OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                             "error sending fragment. ret = %d", ret));
        return ret;
    }

    request->req_complete_cb = cb;
    request->req_complete_cb_data = ctx;

    ret = MCA_PML_CALL(start(1, &request));

    return ret;
}
