init_qp(
    ompi_btl_usnic_module_t* module,
    struct ompi_btl_usnic_channel_t *channel)
{
    struct ibv_qp_attr qp_attr;
    struct ibv_qp_init_attr qp_init_attr;


    memset(&qp_init_attr, 0, sizeof(qp_init_attr));

    qp_init_attr.send_cq = channel->cq;
    qp_init_attr.recv_cq = channel->cq;
    qp_init_attr.cap.max_send_wr = channel->chan_sd_num;
    qp_init_attr.cap.max_recv_wr = channel->chan_rd_num;
    qp_init_attr.cap.max_send_sge = 1;
    qp_init_attr.cap.max_recv_sge = 1;
    qp_init_attr.qp_type = IBV_QPT_UD;


    channel->qp = ibv_create_qp(module->pd, &qp_init_attr);
    if (NULL == channel->qp) {
        opal_show_help("help-mpi-btl-usnic.txt", "create ibv resource failed",
                       true,
                       ompi_process_info.nodename,
                       ibv_get_device_name(module->device),
                       "ibv_create_qp()", __FILE__, __LINE__,
                       "Failed to create a usNIC queue pair");
        return OMPI_ERR_OUT_OF_RESOURCE;
    }


    memset(&qp_attr, 0, sizeof(qp_attr));
    qp_attr.qp_state = IBV_QPS_INIT;
    qp_attr.port_num = module->port_num;

    if (ibv_modify_qp(channel->qp, &qp_attr,
                      IBV_QP_STATE | IBV_QP_PORT)) {
        opal_show_help("help-mpi-btl-usnic.txt", "ibv API failed",
                       true,
                       ompi_process_info.nodename,
                       ibv_get_device_name(module->device),
                       module->port_num,
                       "ibv_modify_qp()", __FILE__, __LINE__,
                       "Failed to modify an existing queue pair");
        return OMPI_ERR_TEMP_OUT_OF_RESOURCE;
    }


    memset(&qp_attr, 0, sizeof(qp_attr));
    memset(&qp_init_attr, 0, sizeof(qp_init_attr));
    if (ibv_query_qp(channel->qp, &qp_attr, IBV_QP_CAP,
                     &qp_init_attr) != 0) {
        opal_show_help("help-mpi-btl-usnic.txt", "ibv API failed",
                       true,
                       ompi_process_info.nodename,
                       ibv_get_device_name(module->device),
                       module->port_num,
                       "ibv_query_qp()", __FILE__, __LINE__,
                       "Failed to query an existing queue pair");
        return OMPI_ERR_TEMP_OUT_OF_RESOURCE;
    }


    if (channel == &module->mod_channels[USNIC_DATA_CHANNEL]) {
        module->qp_max_inline = qp_attr.cap.max_inline_data;
    }

    return OMPI_SUCCESS;
}
