oldmda_find_data_name(const gchar *headername, const gchar *dataname)
{
    gchar *dirname = g_path_get_dirname(headername);
    gchar *data_name = g_path_get_basename(dataname);
    gchar *dname, *filename;

    filename = g_build_filename(dirname, data_name, NULL);
    gwy_debug("trying <%s>", filename);
    if (g_file_test(filename, G_FILE_TEST_IS_REGULAR)) {
        g_free(dirname);
        return filename;
    }
    g_free(filename);

    dname = g_ascii_strup(data_name, -1);
    filename = g_build_filename(dirname, dname, NULL);
    gwy_debug("trying <%s>", filename);
    if (g_file_test(filename, G_FILE_TEST_IS_REGULAR)) {
        g_free(dname);
        g_free(dirname);
        return filename;
    }
    g_free(dname);
    g_free(filename);

    dname = g_ascii_strdown(data_name, -1);
    filename = g_build_filename(dirname, dname, NULL);
    gwy_debug("trying <%s>", filename);
    if (g_file_test(filename, G_FILE_TEST_IS_REGULAR)) {
        g_free(dname);
        g_free(dirname);
        return filename;
    }
    g_free(dname);
    g_free(filename);
    g_free(dirname);

    gwy_debug("failed");

    return NULL;
}
