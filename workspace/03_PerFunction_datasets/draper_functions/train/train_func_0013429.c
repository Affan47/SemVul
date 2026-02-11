globus_l_gfs_data_auth_stat_cb(
    globus_gfs_data_reply_t *           reply,
    void *                              user_arg)
{
    void *                              stat_wrapper;
    globus_result_t                     res;
    globus_gfs_acl_action_t             action;
    int                                 rc;
    globus_l_gfs_data_operation_t *     op;
    globus_gfs_transfer_info_t *        recv_info;
    globus_gfs_acl_object_desc_t        object;
    GlobusGFSName(globus_l_gfs_data_auth_stat_cb);
    GlobusGFSDebugEnter();

    op = (globus_l_gfs_data_operation_t *) user_arg;
    recv_info = (globus_gfs_transfer_info_t *) op->info_struct;

    globus_l_gfs_data_alive(op->session_handle);


    if(reply->info.stat.stat_count == 0)
    {
        action = GFS_ACL_ACTION_CREATE;
    }

    else
    {
        action = GFS_ACL_ACTION_WRITE;
    }
    object.name = recv_info->pathname;
    object.size = recv_info->alloc_size;
    stat_wrapper = op->stat_wrapper;
    rc = globus_gfs_acl_authorize(
        &op->session_handle->acl_handle,
        action,
        &object,
        &res,
        globus_l_gfs_authorize_cb,
        op);
    if(rc == GLOBUS_GFS_ACL_COMPLETE)
    {
        globus_l_gfs_authorize_cb(&object, action, op, res);
    }
    globus_free(stat_wrapper);

    GlobusGFSDebugExit();
}
