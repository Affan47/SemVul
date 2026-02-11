globus_l_gfs_request_active_data(
    globus_gridftp_server_control_op_t  op,
    globus_gridftp_server_control_network_protocol_t net_prt,
    const char **                       cs,
    int                                 cs_count,
    void *                              user_arg)
{
    char *                              tmp_str;
    globus_l_gfs_server_instance_t *    instance;
    globus_gfs_data_info_t *            data_info;
    globus_l_gfs_request_info_t *       request;
    globus_result_t                     result;
    globus_xio_contact_t                parsed_contact;
    GlobusGFSName(globus_l_gfs_request_active_data);
    GlobusGFSDebugEnter();

    instance = (globus_l_gfs_server_instance_t *) user_arg;

    data_info = (globus_gfs_data_info_t *)
        globus_calloc(1, sizeof(globus_gfs_data_info_t));

    result = globus_l_gfs_request_info_init(
        &request, instance, op, data_info);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_init;
    }

    globus_l_gfs_get_data_info(op, data_info, net_prt);
    globus_xio_contact_parse(&parsed_contact, instance->local_contact);

    data_info->contact_strings = cs;
    data_info->cs_count = cs_count;
    data_info->interface = globus_libc_strdup(parsed_contact.host);

    globus_xio_contact_destroy(&parsed_contact);

    globus_i_gfs_data_request_active(
        NULL,
        instance->session_arg,
        0,
        data_info,
        globus_l_gfs_data_active_data_cb,
        request);

    GlobusGFSDebugExit();
    return;

error_init:
    tmp_str = globus_error_print_friendly(globus_error_peek(result));
    globus_gridftp_server_control_finished_active_connect(
        op,
        NULL,
        0,
        GLOBUS_GRIDFTP_SERVER_CONTROL_RESPONSE_ACTION_FAILED,
        tmp_str);
    GlobusGFSDebugExitWithError();
}
