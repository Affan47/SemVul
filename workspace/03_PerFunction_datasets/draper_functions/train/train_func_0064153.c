globus_l_gfs_file_read_cb(
    globus_xio_handle_t                 xio_handle,
    globus_result_t                     result,
    globus_byte_t *                     buffer,
    globus_size_t                       len,
    globus_size_t                       nbytes,
    globus_xio_data_descriptor_t        data_desc,
    void *                              user_arg)
{
    globus_l_file_monitor_t *           monitor;
    GlobusGFSName(globus_l_gfs_file_read_cb);
    GlobusGFSFileDebugEnter();

    monitor = (globus_l_file_monitor_t *) user_arg;

    globus_mutex_lock(&monitor->lock);
    {
        monitor->pending_reads--;
        if(result != GLOBUS_SUCCESS && monitor->error == NULL)
        {
            if(globus_xio_error_is_eof(result))
            {
                monitor->eof = GLOBUS_TRUE;
            }
            else
            {
                monitor->error = GlobusGFSErrorObjWrapFailed(
                    "callback", result);
            }
        }
        if(monitor->error != NULL)
        {
            globus_list_insert(&monitor->buffer_list, buffer);
            goto error;
        }

        if(nbytes > 0)
        {
            result = globus_gridftp_server_register_write(
                monitor->op,
                buffer,
                nbytes,
                monitor->file_offset,
                -1,
                globus_l_gfs_file_server_write_cb,
                monitor);
            if(result != GLOBUS_SUCCESS)
            {
                globus_list_insert(&monitor->buffer_list, buffer);
                monitor->error = GlobusGFSErrorObjWrapFailed(
                    "globus_gridftp_server_register_write", result);
                goto error;
            }

            monitor->pending_writes++;
            monitor->file_offset += nbytes;
            if(monitor->read_length != -1)
            {
                monitor->read_length -= nbytes;
            }
        }
        else
        {
            globus_list_insert(&monitor->buffer_list, buffer);
        }

        if(monitor->read_length == 0)
        {
            monitor->first_read = GLOBUS_TRUE;
        }

        result = globus_l_gfs_file_dispatch_read(monitor);
        if(result != GLOBUS_SUCCESS)
        {
            monitor->error = GlobusGFSErrorObjWrapFailed(
                "globus_l_gfs_file_dispatch_read", result);
            goto error;
        }

        if(monitor->pending_reads == 0 && monitor->pending_writes == 0)
        {
            globus_assert(monitor->eof || monitor->aborted);
            globus_l_gfs_file_close(monitor, GLOBUS_SUCCESS);
            globus_mutex_unlock(&monitor->lock);
        }
        else
        {
            globus_mutex_unlock(&monitor->lock);
        }
    }


    GlobusGFSFileDebugExit();
    return;

error:
    globus_assert(monitor->pending_reads == 0);
    if(monitor->pending_writes != 0)
    {

        globus_mutex_unlock(&monitor->lock);

        GlobusGFSFileDebugExitWithError();
        return;
    }
    globus_l_gfs_file_close(monitor, globus_error_put(monitor->error));
    globus_mutex_unlock(&monitor->lock);

    GlobusGFSFileDebugExitWithError();
}
