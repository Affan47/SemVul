ompi_common_ofacm_base_remote_context_init(ompi_common_ofacm_base_remote_connection_context_t *context,
                                                int num_qps, int num_srqs)
{
    context->rem_qps = (ompi_common_ofacm_base_rem_qp_info_t *)
        calloc(num_qps, sizeof(ompi_common_ofacm_base_rem_qp_info_t));
    if (NULL == context->rem_qps) {
        return OMPI_ERROR;
    }

    context->rem_srqs = (ompi_common_ofacm_base_rem_srq_info_t *)
        calloc(num_qps, sizeof(ompi_common_ofacm_base_rem_srq_info_t));
    if (NULL == context->rem_srqs) {
        return OMPI_ERROR;
    }

    return OMPI_SUCCESS;
}
