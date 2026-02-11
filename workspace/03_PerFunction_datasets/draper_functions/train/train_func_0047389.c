globus_l_gfs_server_detached()
{
    int                                 rc;
    pid_t                               pid;
    GlobusGFSName(globus_l_gfs_server_detached);

    globus_l_gfs_server_build_child_args(GLOBUS_TRUE);

    pid = fork();
    if(pid < 0)
    {
    }

    else if(pid != 0)
    {
        char * pidfile = globus_i_gfs_config_string("pidfile");

        if(pidfile != NULL)
        {
            globus_result_t result;
            char * pidfile_evaled;

            result = globus_eval_path(pidfile, &pidfile_evaled);

            if(result == GLOBUS_SUCCESS)
            {
                mode_t                  oldmask;
                oldmask = umask(022);
                FILE * fh = fopen(pidfile_evaled, "w");
                umask(oldmask);

                if (fh != NULL)
                {
                    fprintf(fh, "%ld\n", (long) pid);
                    fclose(fh);
                }
            }
        }
        exit(0);
    }

    else
    {
        setsid();
        freopen("/dev/null", "w+", stdin);
        freopen("/dev/null", "w+", stdout);
        freopen("/dev/null", "w+", stderr);


        if(*globus_l_gfs_child_argv[0] == '/')
        {
            rc = execv(globus_l_gfs_child_argv[0], globus_l_gfs_child_argv);
        }
        else
        {
            rc = execvp(globus_l_gfs_child_argv[0], globus_l_gfs_child_argv);
        }
        if(rc == -1)
        {
            globus_result_t             result;
            char *                      error_msg;

            error_msg = globus_common_create_string("%s\n%s\n%s\n%s",
                _GSSL("Could not exec process."),
                _GSSL("Please verify that a gridftp server is located at: "),
                globus_l_gfs_child_argv[0],
                _GSSL("Or try the -exec flag."));
            result = GlobusGFSErrorSystemError("execv", errno);
            globus_gfs_log_result(GLOBUS_GFS_LOG_ERR, error_msg, result);

            exit(1);
        }
    }

}
