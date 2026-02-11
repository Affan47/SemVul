parse_cmdline (int argc, char *argv[], glusterfs_ctx_t *ctx)
{
        int               process_mode = 0;
        int               ret = 0;
        struct stat       stbuf = {0, };
        struct tm        *tm = NULL;
        time_t            utime;
        char              timestr[256];
        char              tmp_logfile[1024] = { 0 };
        char              *tmp_logfile_dyn = NULL;
        char              *tmp_logfilebase = NULL;
        cmd_args_t        *cmd_args = NULL;

        cmd_args = &ctx->cmd_args;

        argp_parse (&argp, argc, argv, ARGP_IN_ORDER, NULL, cmd_args);

        if (ENABLE_DEBUG_MODE == cmd_args->debug_mode) {
                cmd_args->log_level = GF_LOG_DEBUG;
                cmd_args->log_file = "/dev/stderr";
                cmd_args->no_daemon_mode = ENABLE_NO_DAEMON_MODE;
        }

        process_mode = gf_get_process_mode (argv[0]);
        ctx->process_mode = process_mode;


        if (cmd_args->volfile_server && !cmd_args->volfile_id) {
                gf_log ("glusterfs", GF_LOG_CRITICAL,
                        "ERROR: '--volfile-id' is mandatory if '-s' OR "
                        "'--volfile-server' option is given");
                ret = -1;
                goto out;
        }

        if ((cmd_args->volfile_server == NULL)
            && (cmd_args->volfile == NULL)) {
                if (process_mode == GF_SERVER_PROCESS)
                        cmd_args->volfile = gf_strdup (DEFAULT_SERVER_VOLFILE);
                else if (process_mode == GF_GLUSTERD_PROCESS)
                        cmd_args->volfile = gf_strdup (DEFAULT_GLUSTERD_VOLFILE);
                else
                        cmd_args->volfile = gf_strdup (DEFAULT_CLIENT_VOLFILE);


                ret = stat (cmd_args->volfile, &stbuf);
                if (ret) {
                        gf_log ("glusterfs", GF_LOG_CRITICAL,
                                "ERROR: parsing the volfile failed (%s)\n",
                                strerror (errno));

                        fprintf (stderr, "USAGE: %s [options] [mountpoint]\n",
                                 argv[0]);
                        goto out;
                }
        }

        if (cmd_args->run_id) {
                ret = sys_lstat (cmd_args->log_file, &stbuf);


                if (((ret == 0) &&
                     (S_ISREG (stbuf.st_mode) || S_ISLNK (stbuf.st_mode))) ||
                    (ret == -1)) {

                        tm = localtime (&utime);
                        strftime (timestr, 256, "%Y%m%d.%H%M%S", tm);
                        sprintf (tmp_logfile, "%s.%s.%d",
                                 cmd_args->log_file, timestr, getpid ());


                        sys_unlink (cmd_args->log_file);

                        tmp_logfile_dyn = gf_strdup (tmp_logfile);
                        tmp_logfilebase = basename (tmp_logfile_dyn);
                        ret = sys_symlink (tmp_logfilebase,
                                           cmd_args->log_file);
                        if (ret == -1) {
                                fprintf (stderr, "ERROR: symlink of logfile failed\n");
                                goto out;
                        }

                        GF_FREE (cmd_args->log_file);
                        cmd_args->log_file = gf_strdup (tmp_logfile);

                        GF_FREE (tmp_logfile_dyn);
                }
        }

#ifdef GF_DARWIN_HOST_OS
        if (cmd_args->mount_point)
                cmd_args->mac_compat = GF_OPTION_DEFERRED;
#endif

        ret = 0;
out:
        return ret;
}
