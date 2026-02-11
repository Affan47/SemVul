globus_l_gfs_remote_init_bounce_info(
    globus_l_gfs_remote_ipc_bounce_t ** bounce,
    globus_gfs_operation_t              op,
    void *                              state,
    globus_l_gfs_remote_handle_t *      my_handle)
{
    globus_l_gfs_remote_ipc_bounce_t *  bounce_info;
    globus_result_t                     result;
    GlobusGFSName(globus_l_gfs_remote_init_bounce_info);
    GlobusGFSRemoteDebugEnter();

    bounce_info = (globus_l_gfs_remote_ipc_bounce_t *)
        globus_calloc(1, sizeof(globus_l_gfs_remote_ipc_bounce_t));
    if(!bounce_info)
    {
        result = GlobusGFSErrorMemory("bounce_info");
        goto error_alloc;
    }

    bounce_info->op = op;
    bounce_info->state = state;
    bounce_info->my_handle = my_handle;
    *bounce = bounce_info;

    GlobusGFSRemoteDebugExit();
    return GLOBUS_SUCCESS;

error_alloc:
    GlobusGFSRemoteDebugExitWithError();
    return result;
}
