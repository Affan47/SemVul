globus_gfs_acl_cas_destroy(
    void *                              out_handle)
{
    globus_gsi_authz_handle_t           cas_handle;
    GlobusGFSName(globus_gfs_acl_cas_destroy);
    GlobusGFSDebugEnter();

    cas_handle = (globus_gsi_authz_handle_t) out_handle;
    globus_gsi_authz_handle_destroy(
        cas_handle, globus_gfs_acl_cas_destroy_cb, NULL);

    GlobusGFSDebugExit();
}
