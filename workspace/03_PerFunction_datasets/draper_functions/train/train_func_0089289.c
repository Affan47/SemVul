globus_i_gfs_data_request_stat(
    globus_gfs_ipc_handle_t             ipc_handle,
    void *                              session_arg,
    int                                 id,
    globus_gfs_stat_info_t *            stat_info,
    globus_i_gfs_data_callback_t        cb,
    void *                              user_arg)
{
    globus_result_t                     res;
    int                                 rc;
    globus_l_gfs_data_operation_t *     op;
    globus_result_t                     result;
    globus_l_gfs_data_session_t *       session_handle;
    globus_gfs_acl_object_desc_t        object;
    GlobusGFSName(globus_i_gfs_data_request_stat);
    GlobusGFSDebugEnter();

    session_handle = (globus_l_gfs_data_session_t *) session_arg;
    globus_l_gfs_data_reset_watchdog(session_handle, NULL);

    result = globus_l_gfs_data_operation_init(&op, session_handle);
    if(result != GLOBUS_SUCCESS)
    {
        result = GlobusGFSErrorWrapFailed(
            "globus_l_gfs_data_operation_init", result);
        goto error_op;
    }

    op->ipc_handle = ipc_handle;
    op->id = id;
    op->uid = getuid();

    op->state = GLOBUS_L_GFS_DATA_REQUESTING;
    op->callback = cb;
    op->user_arg = user_arg;
    op->session_handle = session_handle;
    op->info_struct = stat_info;
    op->type = GLOBUS_L_GFS_DATA_INFO_TYPE_STAT;

    object.name = stat_info->pathname;

    if(stat_info->internal)
    {
        res = GLOBUS_SUCCESS;
        rc = GLOBUS_GFS_ACL_COMPLETE;
    }
    else
    {
        rc = globus_gfs_acl_authorize(
            &session_handle->acl_handle,
            GFS_ACL_ACTION_LOOKUP,
            &object,
            &res,
            globus_l_gfs_authorize_cb,
            op);
    }
    if(rc == GLOBUS_GFS_ACL_COMPLETE)
    {

        globus_l_gfs_authorize_cb(
            &object, GFS_ACL_ACTION_LOOKUP, op, res);
    }

    GlobusGFSDebugExit();
    return;

error_op:
    globus_l_gfs_authorize_cb(
        &object, GFS_ACL_ACTION_LOOKUP, op, result);
    GlobusGFSDebugExitWithError();
}
