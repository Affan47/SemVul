globus_l_gfs_ipc_handshake_write_cb(
    globus_xio_handle_t                 handle,
    globus_result_t                     result,
    globus_byte_t *                     buffer,
    globus_size_t                       len,
    globus_size_t                       nbytes,
    globus_xio_data_descriptor_t        data_desc,
    void *                              user_arg)
{
    globus_byte_t *                     new_buf;
    globus_i_gfs_ipc_handle_t *         ipc;
    GlobusGFSName(globus_l_gfs_ipc_handshake_write_cb);
    GlobusGFSDebugEnter();

    ipc = (globus_i_gfs_ipc_handle_t *) user_arg;

    globus_mutex_lock(&ipc->mutex);
    {
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }

        if(globus_l_gfs_ipc_requester)
        {
            result = globus_l_gfs_ipc_send_start_session(ipc);
            if(result != GLOBUS_SUCCESS)
            {
                goto error;
            }
        }
        else
        {

            new_buf = globus_malloc(GFS_IPC_HEADER_SIZE);
            if(new_buf == NULL)
            {
                goto error;
            }
            result = globus_xio_register_read(
                ipc->xio_handle,
                new_buf,
                GFS_IPC_HEADER_SIZE,
                GFS_IPC_HEADER_SIZE,
                NULL,
                globus_l_gfs_ipc_reply_read_header_cb,
                ipc);
            if(result != GLOBUS_SUCCESS)
            {
                goto read_error;
            }
        }
    }
    globus_mutex_unlock(&ipc->mutex);

    globus_free(buffer);

    GlobusGFSDebugExit();
    return;

read_error:
    globus_free(new_buf);
error:
    ipc->cached_res = result;
    globus_free(buffer);
    ipc->state = GLOBUS_GFS_IPC_STATE_ERROR;
    globus_mutex_unlock(&ipc->mutex);

    if(ipc->open_cb)
    {
        ipc->open_cb(ipc, result, NULL, ipc->user_arg);
    }

    GlobusGFSDebugExitWithError();
}
