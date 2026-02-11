cut_init_environment (int *argc, char ***argv)
{
    if (environment_initialized)
        return;

    environment_initialized = TRUE;

    cut_set_cutter_command_path((*argv)[0]);

    setlocale(LC_ALL, "");

#ifdef G_OS_WIN32
    {
        gchar *locale_dir;
        locale_dir = g_build_filename(cut_win32_base_path(),
                                      "share", "locale", NULL);
        bindtextdomain(GETTEXT_PACKAGE, locale_dir);
        g_free(locale_dir);
    }
#else
    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
#endif
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    g_type_init();
    if (!g_thread_supported())
        g_thread_init(NULL);

    gcut_init();
}
