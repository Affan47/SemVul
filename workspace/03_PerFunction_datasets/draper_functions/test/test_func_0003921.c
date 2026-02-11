get_x11_server_pid (SessionInfo *si,
                    gboolean    *can_connect,
                    guint       *pid)
{
        gboolean   res;
        char      *err;
        char      *out;
        int        status;
        int        i;
        GError    *error;
        guint      num;
        char      *argv[4];
        GPtrArray *env;

        if (can_connect != NULL) {
                *can_connect = FALSE;
        }
        if (pid != NULL) {
                *pid = 0;
        }


        env = get_filtered_environment (si->pid);

        num = 0;

        argv[0] = LIBEXECDIR "/ck-get-x11-server-pid";
        argv[1] = NULL;

        error = NULL;
        out = NULL;
        err = NULL;
        status = -1;
        res = g_spawn_sync (NULL,
                            argv,
                            (char **)env->pdata,
                            0,
                            (GSpawnChildSetupFunc)setuid_child_setup_func,
                            si,
                            &out,
                            &err,
                            &status,
                            &error);
        for (i = 0; i < env->len; i++) {
                g_free (g_ptr_array_index (env, i));
        }
        g_ptr_array_free (env, TRUE);

        if (error != NULL) {
                g_warning ("Unable to PID for x11 server: %s", error->message);
                g_error_free (error);
        }

        if (status == 0) {
                if (res && out != NULL) {
                        guint v;
                        char  c;

                        if (1 == sscanf (out, "%u %c", &v, &c)) {
                                num = v;
                        }
                }

                if (can_connect != NULL) {
                        *can_connect = TRUE;
                }
        }


        if (err != NULL && err[0] != '\0') {
                g_warning ("%s", err);
        }

        if (pid != NULL) {
                *pid = num;
        }

        g_free (out);
        g_free (err);
}
