globus_gridftp_server_embed_start(
    globus_gfs_embed_handle_t           handle,
    globus_gfs_embed_event_cb_t         event_cb,
    void *                              user_arg)
{
    globus_result_t                     result;
    GlobusGFSName(globus_gridftp_server_embed_start);
    GlobusGFSDebugEnter();

    handle->event_cb = event_cb;
    handle->event_arg = user_arg;

    result = globus_l_gfs_be_daemon(handle);

    GlobusGFSDebugExit();
    return result;
}
