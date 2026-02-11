ompi_common_ofacm_base_context_init(ompi_common_ofacm_base_local_connection_context_t *context,
                                         ompi_common_ofacm_base_module_t *cpc,
                                         ompi_common_ofacm_base_context_connect_cb_fn_t connect_cb,
                                         ompi_common_ofacm_base_context_error_cb_fn_t error_cb,
                                         ompi_common_ofacm_base_context_prepare_recv_cb_fn_t prepare_recv_cb,
                                         ompi_common_ofacm_base_proc_t *proc,
                                         ompi_common_ofacm_base_qp_config_t *qp_config,
                                         struct ibv_pd *pd, uint64_t subnet_id, int cpc_type,
                                         uint16_t lid, uint16_t rem_lid,
                                         int32_t user_context_index, void *user_context)
{
    context->proc = proc;
    context->cpc = cpc;
    context->subnet_id = subnet_id;
    context->cpc_type = cpc_type;
    context->lid = lid;
    context->rem_lid = rem_lid;
    context->num_of_qps = qp_config->num_qps;

    if (NULL == context->qps) {
        context->qps = calloc(context->num_of_qps, sizeof(ompi_common_ofacm_base_qp_t));
        if(NULL == context->qps) {
            OFACM_ERROR(("Failed to allocate memory for qps"));
            return OMPI_ERR_OUT_OF_RESOURCE;
        }
    }

    context->num_of_srqs = qp_config->num_srqs;
    context->srq_num = qp_config->srq_num;
    context->init_attr = qp_config->init_attr;
    context->attr = qp_config->attr;
    context->custom_init_attr_mask = qp_config->init_attr_mask;
    context->custom_rtr_attr_mask = qp_config->rtr_attr_mask;
    context->custom_rts_attr_mask = qp_config->rts_attr_mask;
    context->ib_pd = pd;
    context->connect_cb = connect_cb;
    context->error_cb = error_cb;
    context->prepare_recv_cb = prepare_recv_cb ;
    context->index = user_context_index;
    context->user_context = user_context;
    return OMPI_SUCCESS;
}
