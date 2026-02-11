ck_unix_pid_get_uid (pid_t pid)
{
        struct stat st;
        char       *path;
        int         uid;
        int         res;

        g_return_val_if_fail (pid > 1, 0);

        uid = -1;

        path = g_strdup_printf ("/proc/%u", (guint)pid);
        res = stat (path, &st);
        g_free (path);

        if (res == 0) {
                uid = st.st_uid;
        }

        return uid;
}
