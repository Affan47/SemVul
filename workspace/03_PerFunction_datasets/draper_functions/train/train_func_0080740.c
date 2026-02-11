convert_filename(const gchar *filename) {
    if (filename) {
        if (strncmp("~/", filename, 2) == 0)
            return g_build_filename(g_get_home_dir(), filename + 2, NULL);
        else
            return g_strdup(filename);
    }

    return NULL;
}
