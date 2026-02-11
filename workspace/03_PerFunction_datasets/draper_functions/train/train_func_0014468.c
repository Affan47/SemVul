find_plugin_executables(const gchar *dir,
                        GSList *list,
                        gint level)
{
    const gchar *filename;
    gchar *pluginname;
    GError *err = NULL;
    GDir *gdir;

    if (level-- < 0)
        return list;

    gdir = g_dir_open(dir, 0, &err);
    if (err) {
        gwy_debug("Cannot open plug-in directory %s: %s", dir, err->message);
        g_clear_error(&err);
        return NULL;
    }
    gwy_debug("Scanning directory %s", dir);
    while ((filename = g_dir_read_name(gdir))) {
        if (gwy_filename_ignore(filename)) {
            gwy_debug("Ignoring %s (ignorable file)", filename);
            continue;
        }
        pluginname = g_build_filename(dir, filename, NULL);
        if (g_file_test(pluginname, G_FILE_TEST_IS_DIR)) {
            gwy_debug("%s is a directory, descending", filename);
            list = find_plugin_executables(pluginname, list, level);
            g_free(pluginname);
            continue;
        }
        if (g_str_has_suffix(filename, ".rgi")
            || g_str_has_suffix(filename, ".RGI")) {
            gwy_debug("Ignoring %s, it is a RGI file", filename);
            g_free(pluginname);
            continue;
        }
        if (!g_file_test(pluginname, G_FILE_TEST_IS_EXECUTABLE)) {
            gwy_debug("Ignoring %s, is not executable", filename);
            g_free(pluginname);
            continue;
        }
#ifdef G_OS_WIN32
        if (!g_str_has_suffix(filename, ".exe")
            && !g_str_has_suffix(filename, ".EXE")) {
            gwy_debug("[Win32] Ignoring %s, is not .exe", filename);
            g_free(pluginname);
            continue;
        }
        if (g_str_has_prefix(filename, "unins")
            || g_str_has_prefix(filename, "UNINS")) {
            gwy_debug("[Win32] Ignoring %s, is uninstaller", filename);
            g_free(pluginname);
            continue;
        }
#endif
        gwy_debug("plug-in %s", filename);
        list = g_slist_prepend(list, pluginname);
    }

    g_dir_close(gdir);

    return list;
}
