globus_l_gfs_reject_open_cb(
    globus_xio_handle_t                 handle,
    globus_result_t                     result,
    void *                              user_arg)
{
    char *                              sorry_msg;
    char *                              tmp_msg;
    int                                 len;

    if(globus_gfs_config_get_int("connections_max") == 0 ||
        globus_i_gfs_config_bool("connections_disabled"))
    {
        if((tmp_msg = globus_gfs_config_get_string("offline_msg")) != NULL)
        {
            sorry_msg = globus_common_create_string("422 %s\r\n", tmp_msg);
        }
        else
        {
            sorry_msg = globus_libc_strdup(
                "422 Service temporarily offline. Closing control connection.\r\n");
        }
    }
    else
    {
        sorry_msg = globus_libc_strdup(
            "421 Service busy: Connection limit exceeded. Please try again "
            "later. Closing control connection.\r\n");
    }

    len = strlen(sorry_msg);
    globus_mutex_lock(&globus_l_gfs_mutex);
    {
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }

        result = globus_xio_register_write(
            handle,
            sorry_msg,
            len,
            len,
            NULL,
            globus_l_gfs_reject_write_cb,
            sorry_msg);
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }
    }
    globus_mutex_unlock(&globus_l_gfs_mutex);

    return;

error:
    globus_free(sorry_msg);
    result = globus_xio_register_close(
        handle,
        NULL,
        globus_l_gfs_reject_close_cb,
        NULL);
    if(result != GLOBUS_SUCCESS)
    {
        globus_l_gfs_outstanding--;
    }
    globus_mutex_unlock(&globus_l_gfs_mutex);
}
