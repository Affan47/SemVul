globus_gridftp_server_finished_stat_custom_list(
    globus_gfs_operation_t              op,
    globus_result_t                     result,
    globus_byte_t *                     list_response,
    globus_size_t                       list_response_len,
    globus_bool_t                       free_buffer)
{
    globus_l_gfs_data_stat_bounce_t *   bounce_info;
    globus_l_gfs_data_operation_t *     data_op;
    globus_bool_t                       destroy_session = GLOBUS_FALSE;
    globus_bool_t                       destroy_op = GLOBUS_FALSE;
    GlobusGFSName(globus_gridftp_server_finished_stat_custom_list);
    GlobusGFSDebugEnter();

    data_op = (globus_l_gfs_data_operation_t *) op->user_arg;

    globus_l_gfs_data_alive(op->session_handle);

    if(result != GLOBUS_SUCCESS)
    {
        goto error;
    }

    bounce_info = (globus_l_gfs_data_stat_bounce_t *)
        globus_calloc(sizeof(globus_l_gfs_data_stat_bounce_t), 1);
    if(bounce_info == NULL)
    {
        result = GlobusGFSErrorMemory("bounce_info");
        goto error;
    }

    bounce_info->custom_list = GLOBUS_TRUE;
    bounce_info->free_buffer = free_buffer;
    if(free_buffer)
    {
        bounce_info->list_response = list_response;
    }
    else
    {
        bounce_info->list_response = globus_malloc(list_response_len);
        memcpy(bounce_info->list_response, list_response, list_response_len);
    }

    globus_gridftp_server_begin_transfer(data_op, 0, NULL);

    result = globus_gridftp_server_register_write(
        data_op,
        bounce_info->list_response,
        list_response_len,
        0,
        -1,
        globus_l_gfs_data_list_write_cb,
        bounce_info);
    if(result != GLOBUS_SUCCESS)
    {
        result = GlobusGFSErrorWrapFailed(
            "globus_gridftp_server_register_write", result);
        goto error;
    }

    globus_mutex_lock(&op->session_handle->mutex);
    {
        GFSDataOpDec(op, destroy_op, destroy_session);
    }
    globus_mutex_unlock(&op->session_handle->mutex);
    globus_assert(destroy_op);
    globus_l_gfs_data_operation_destroy(op);

    globus_free(data_op->stat_wrapper);

    GlobusGFSDebugExit();
    return;

error:
    globus_gridftp_server_finished_transfer(data_op, result);
    GlobusGFSDebugExitWithError();
}
