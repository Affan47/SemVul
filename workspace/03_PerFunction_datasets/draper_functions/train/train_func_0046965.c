cl5WriteRUV()
{
    int rc = 0;
    Object *file_obj = NULL;
    CL5DBFile *dbfile = NULL;
    int closeit = 0;
    int slapd_pid = 0;

    changelog5Config config;


    changelog5_read_config (&config);
    if (config.dir == NULL) {


        goto bail;
    }

    slapd_pid = is_slapd_running();
    if (slapd_pid <= 0) {


        goto bail;
    }

    if (getpid() != slapd_pid) {


        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
                     "cl5WriteRUV: server (pid %d) is already running; bail.\n",
                     slapd_pid);
        rc = 1;
        goto bail;
    }


    if (CL5_STATE_OPEN != s_cl5Desc.dbState) {
        rc = _cl5Open(config.dir, &config.dbconfig, CL5_OPEN_NORMAL);
        if (rc != CL5_SUCCESS) {
            slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
                            "cl5WriteRUV: failed to open changelog\n");
            goto bail;
        }
        s_cl5Desc.dbState = CL5_STATE_OPEN;
        closeit = 1;
    }

    file_obj = objset_first_obj(s_cl5Desc.dbFiles);
    while (file_obj) {
        dbfile = (CL5DBFile *)object_get_data(file_obj);
        if (dbfile) {
            _cl5WriteEntryCount(dbfile);
            _cl5WriteRUV(dbfile, PR_TRUE);
            _cl5WriteRUV(dbfile, PR_FALSE);
        }
        file_obj = objset_next_obj(s_cl5Desc.dbFiles, file_obj);
    }
bail:
    if (closeit && (CL5_STATE_OPEN == s_cl5Desc.dbState)) {
        _cl5Close ();
        s_cl5Desc.dbState = CL5_STATE_CLOSED;
    }
    changelog5_config_done(&config);
    return rc;
}
