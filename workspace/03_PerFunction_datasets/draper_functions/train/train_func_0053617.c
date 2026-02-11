gwy_load_modules_in_dir(GDir *gdir,
                        const gchar *dirname,
                        GHashTable *mods)
{
    const gchar *filename;
    gchar *modulename;

    modulename = NULL;
    while ((filename = g_dir_read_name(gdir))) {
        if (g_str_has_prefix(filename, "."))
            continue;
#ifdef G_OS_WIN32
        if (!gwy_str_has_suffix_nocase(filename, "." G_MODULE_SUFFIX))
#else
        if (!g_str_has_suffix(filename, "." G_MODULE_SUFFIX))
#endif
            continue;
        modulename = g_build_filename(dirname, filename, NULL);
        gwy_module_do_register_module(modulename, mods, NULL);
        g_free(modulename);
    }
}
