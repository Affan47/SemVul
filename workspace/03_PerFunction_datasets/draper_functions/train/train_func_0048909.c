create_process_manager(server_rec * main_server, apr_pool_t * configpool)
{
    apr_status_t rv;

    g_process_manager =
        (apr_proc_t *) apr_pcalloc(configpool, sizeof(*g_process_manager));
    rv = apr_proc_fork(g_process_manager, configpool);
    if (rv == APR_INCHILD) {

        g_pm_pid = getpid();
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, main_server,
                     "mod_fcgid: Process manager %" APR_PID_T_FMT  " started", getpid());

        if ((rv = init_signal(main_server)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, main_server,
                         "mod_fcgid: can't install signal handler, exiting now");
            exit(DAEMON_STARTUP_ERROR);
        }


        if (ap_unixd_config.suexec_enabled) {
            if (getuid() != 0) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, main_server,
                             "mod_fcgid: current user is not root while suexec is enabled, exiting now");
                exit(DAEMON_STARTUP_ERROR);
            }
            suexec_setup_child();
        } else
            ap_unixd_setup_child();
        apr_file_pipe_timeout_set(g_pm_read_pipe,
                                  apr_time_from_sec(g_wakeup_timeout));
        apr_file_close(g_ap_write_pipe);
        apr_file_close(g_ap_read_pipe);


        spawn_control_init(main_server, configpool);

        pm_main(main_server, configpool);

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, main_server,
                     "mod_fcgid: Process manager %" APR_PID_T_FMT " stopped", getpid());
        exit(0);
    } else if (rv != APR_INPARENT) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, main_server,
                     "mod_fcgid: Create process manager error");
        exit(1);
    }


    apr_pool_note_subprocess(configpool, g_process_manager,
                             APR_KILL_ONLY_ONCE);
    apr_proc_other_child_register(g_process_manager, fcgid_maint,
                                  g_process_manager, NULL, configpool);

    return APR_SUCCESS;
}
