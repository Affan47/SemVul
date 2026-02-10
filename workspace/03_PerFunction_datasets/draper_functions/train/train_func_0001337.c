globus_l_gfs_data_active_kickout(
    void *                              user_arg)
{
    globus_l_gfs_data_active_bounce_t * bounce_info;
    globus_gfs_finished_info_t              reply;
    GlobusGFSName(globus_l_gfs_data_active_kickout);
    GlobusGFSDebugEnter();

    bounce_info = (globus_l_gfs_data_active_bounce_t *) user_arg;

    memset(&reply, '\0', sizeof(globus_gfs_finished_info_t));
    reply.type = GLOBUS_GFS_OP_ACTIVE;
    reply.id = bounce_info->id;
    reply.result = bounce_info->result;
    reply.info.data.bi_directional = bounce_info->bi_directional;


    if(bounce_info->result == GLOBUS_SUCCESS)
    {
        bounce_info->handle->state = GLOBUS_L_GFS_DATA_HANDLE_VALID;
        bounce_info->handle->is_mine = GLOBUS_TRUE;

        reply.info.data.data_arg = (void *) globus_handle_table_insert(
            &bounce_info->handle->session_handle->handle_table,
            bounce_info->handle,
            1);
    }
    else
    {
        globus_assert(bounce_info->handle == NULL);
    }

    if(bounce_info->callback != NULL)
    {
        bounce_info->callback(
            &reply,
            bounce_info->user_arg);
    }
    else
    {
        globus_gfs_ipc_reply_finished(
            bounce_info->ipc_handle,
            &reply);
    }

    globus_free(bounce_info);

    GlobusGFSDebugExit();
}
