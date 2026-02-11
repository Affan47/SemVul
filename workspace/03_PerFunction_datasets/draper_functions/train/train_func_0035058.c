globus_l_gfs_open_new_server(
    globus_gfs_embed_handle_t           handle,
    globus_xio_handle_t                 xio_handle)
{
    globus_result_t                     result;
    GlobusGFSName(globus_l_gfs_open_new_server);
    GlobusGFSDebugEnter();


    result = globus_xio_register_open(
        xio_handle,
        NULL,
        NULL,
        globus_l_gfs_new_server_cb,
        handle);
    if(result != GLOBUS_SUCCESS)
    {
        goto error_open;
    }
    globus_gfs_config_inc_int("open_connections_count", 1);

    GlobusGFSDebugExit();
    return GLOBUS_SUCCESS;

error_open:
    GlobusGFSDebugExitWithError();
    return result;
}
