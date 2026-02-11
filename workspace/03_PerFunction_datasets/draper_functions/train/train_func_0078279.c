ompi_osc_rdma_rput(void *origin_addr, int origin_count,
                       struct ompi_datatype_t *origin_dt,
                       int target, OPAL_PTRDIFF_TYPE target_disp,
                       int target_count, struct ompi_datatype_t *target_dt,
                       struct ompi_win_t *win, struct ompi_request_t **request)
{
    ompi_osc_rdma_request_t *rdma_request;
    int ret;

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "rput: 0x%lx, %d, %s, %d, %d, %d, %s, %s",
                         (unsigned long) origin_addr, origin_count,
                         origin_dt->name, target, (int) target_disp,
                         target_count, target_dt->name, win->w_name));

    OMPI_OSC_RDMA_REQUEST_ALLOC(win, rdma_request);
    if (NULL == rdma_request) {
        return OMPI_ERR_OUT_OF_RESOURCE;
    }


    if (0 == origin_count || 0 == target_count) {
        ompi_osc_rdma_request_complete (rdma_request, MPI_SUCCESS);
        *request = &rdma_request->super;
        return OMPI_SUCCESS;
    }

    rdma_request->type = OMPI_OSC_RDMA_HDR_TYPE_PUT;

    ret = ompi_osc_rdma_put_w_req (origin_addr, origin_count, origin_dt, target,
                                   target_disp, target_count, target_dt, win,
                                   rdma_request);
    if (OMPI_SUCCESS != ret) {
        OMPI_OSC_RDMA_REQUEST_RETURN(rdma_request);
        return ret;
    }

    *request = (ompi_request_t *) rdma_request;

    return OMPI_SUCCESS;
}
