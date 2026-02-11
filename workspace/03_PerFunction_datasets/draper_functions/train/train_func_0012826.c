globus_l_gfs_sighup(
    void *                              user_arg)
{
    int                                 argc;
    char **                             argv;
    GlobusGFSName(globus_l_gfs_sighup);
    GlobusGFSDebugEnter();

    globus_gfs_log_message(
        GLOBUS_GFS_LOG_INFO,
        "Reloading config...\n");

    argv = (char **) globus_i_gfs_config_get("argv");
    argc = globus_i_gfs_config_int("argc");

    globus_i_gfs_config_init(argc, argv, GLOBUS_FALSE);
    globus_gfs_log_message(
        GLOBUS_GFS_LOG_INFO,
        "Done reloading config.\n");

    GlobusGFSDebugExit();
}
