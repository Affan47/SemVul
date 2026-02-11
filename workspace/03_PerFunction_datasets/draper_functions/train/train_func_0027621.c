rotate_logs (const char *path,
             guint       n_copies)
{
        int i;

        for (i = n_copies - 1; i > 0; i--) {
                char *name_n;
                char *name_n1;

                name_n = g_strdup_printf ("%s.%d", path, i);
                if (i > 1) {
                        name_n1 = g_strdup_printf ("%s.%d", path, i - 1);
                } else {
                        name_n1 = g_strdup (path);
                }

                VE_IGNORE_EINTR (g_unlink (name_n));
                VE_IGNORE_EINTR (g_rename (name_n1, name_n));

                g_free (name_n1);
                g_free (name_n);
        }

        VE_IGNORE_EINTR (g_unlink (path));
}
