globus_l_gfs_data_list_write_cb(
    globus_gfs_operation_t              op,
    globus_result_t                     result,
    globus_byte_t *                     buffer,
    globus_size_t                       nbytes,
    void *                              user_arg)
{
    globus_l_gfs_data_stat_bounce_t *   bounce_info;
    globus_bool_t                       finish = GLOBUS_FALSE;

    GlobusGFSName(globus_l_gfs_data_list_write_cb);
    GlobusGFSDebugEnter();

    globus_l_gfs_data_alive(op->session_handle);

    bounce_info = (globus_l_gfs_data_stat_bounce_t *) user_arg;

    if(!bounce_info->custom_list)
    {
        globus_gridftp_server_control_list_buffer_free(buffer);
    }
    else if(bounce_info->free_buffer)
    {
        globus_free(bounce_info->list_response);
    }

    globus_mutex_lock(&op->stat_lock);
    if(bounce_info->final_stat && !globus_l_gfs_data_request_next_path(op))
    {
        finish = GLOBUS_TRUE;
    }
    globus_mutex_unlock(&op->stat_lock);

    globus_free(bounce_info);

    if(op->delayed_error != GLOBUS_SUCCESS)
    {
        result = op->delayed_error;
    }

    if(finish)
    {
        globus_l_gfs_data_list_done(op, result);
    }

    GlobusGFSDebugExit();
}
