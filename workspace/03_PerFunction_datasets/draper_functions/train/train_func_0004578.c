globus_gfs_ipc_close(
    globus_gfs_ipc_handle_t             ipc_handle,
    globus_gfs_ipc_close_callback_t     cb,
    void *                              user_arg)
{
    globus_result_t                     result;
    GlobusGFSName(globus_gfs_ipc_close);
    GlobusGFSDebugEnter();

    globus_mutex_lock(&ipc_handle->mutex);
    {
        result = globus_l_gfs_ipc_close(ipc_handle, cb, user_arg);
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }
    }
    globus_mutex_unlock(&ipc_handle->mutex);

    GlobusGFSDebugExit();
    return GLOBUS_SUCCESS;
error:
    globus_mutex_unlock(&ipc_handle->mutex);
    globus_mutex_lock(&globus_l_ipc_mutex);
    {
        globus_list_remove(&globus_l_ipc_handle_list,
            globus_list_search(globus_l_ipc_handle_list, ipc_handle));
    }
    globus_mutex_unlock(&globus_l_ipc_mutex);
    globus_l_gfs_ipc_handle_destroy(ipc_handle);

    return result;
}
