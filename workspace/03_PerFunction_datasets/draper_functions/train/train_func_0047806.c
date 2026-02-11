mkdirhier(const gchar *dirname, gboolean silent) {
    gchar *dn, *p;

    g_return_val_if_fail (dirname && *dirname, FALSE);

    if (strncmp("~/", dirname, 2) == 0)
        dn = g_build_filename(g_get_home_dir(), dirname + 2, NULL);
    else
        dn = g_strdup(dirname);

    p = dn;

    do {
        ++p;
        p = index(p, G_DIR_SEPARATOR);

        if (p)
            *p = '\0';

        if (!g_file_test(dn, G_FILE_TEST_EXISTS)) {
            if (g_mkdir(dn, 0777) == -1) {
                if (!silent) {
                    gtkpod_warning(_("Error creating %s: %s\n"), dn, g_strerror(errno));
                }
                g_free(dn);
                return FALSE;
            }
        }
        if (p)
            *p = G_DIR_SEPARATOR;
    }
    while (p);

    g_free(dn);
    return TRUE;
}
