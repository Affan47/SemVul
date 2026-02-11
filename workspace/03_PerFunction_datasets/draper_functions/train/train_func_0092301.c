globus_gfs_acl_test_init(
    void **                             out_handle,
    globus_gfs_acl_info_t *             acl_info,
    globus_gfs_acl_handle_t             acl_handle,
    globus_result_t *                   out_res)
{
    globus_gfs_acl_action_t             fail_str;
    GlobusGFSName(globus_gfs_acl_test_init);
    GlobusGFSDebugEnter();

    fail_str = globus_i_gfs_config_int("test_acl");
    if(fail_str == -1 || fail_str == GFS_ACL_ACTION_INIT)
    {
        *out_res = GlobusACLTestFailure();
    }
    else
    {
        *out_res = GLOBUS_SUCCESS;
    }
    if(fail_str & 0x1000)
    {
        globus_gfs_acl_authorized_finished(acl_handle, *out_res);
        GlobusGFSDebugExit();
        return GLOBUS_GFS_ACL_WOULD_BLOCK;
    }
    else
    {
        GlobusGFSDebugExitWithError();
        return GLOBUS_GFS_ACL_COMPLETE;
    }
}
