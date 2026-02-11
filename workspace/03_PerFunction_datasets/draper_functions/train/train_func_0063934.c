globus_l_gfs_channel_close_cb(
    globus_xio_handle_t                 handle,
    globus_result_t                     result,
    void *                              user_arg)
{
    globus_l_gfs_server_instance_t *    instance;
    GlobusGFSName(globus_l_gfs_channel_close_cb);
    GlobusGFSDebugEnter();

    instance = (globus_l_gfs_server_instance_t *) user_arg;

    globus_gfs_log_message(
        GLOBUS_GFS_LOG_INFO,
        _FSSL("Closed connection from %s\n",NULL),
        instance->remote_contact);
    globus_gfs_log_event(
        GLOBUS_GFS_LOG_INFO,
        GLOBUS_GFS_LOG_EVENT_END,
        "session",
        0,
        "remotehost=%s", instance->remote_contact);


    if(instance->session_arg != NULL)
    {
        globus_i_gfs_data_session_stop(NULL, instance->session_arg);
    }
    if(instance->close_func)
    {
        instance->close_func(instance->close_arg, instance->close_error);
    }

    if(instance->home_dir)
    {
        globus_free(instance->home_dir);
    }
    if(instance->username)
    {
        globus_free(instance->username);
    }
    if(instance->scks_alg)
    {
        globus_free(instance->scks_alg);
    }
    if(instance->scks_val)
    {
        globus_free(instance->scks_val);
    }
    globus_free(instance->local_contact);
    globus_free(instance->remote_contact);
    globus_free(instance);

    GlobusGFSDebugExit();
}
