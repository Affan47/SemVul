main (int    argc,
      char **argv)
{
        GMainLoop        *main_loop;
        GOptionContext   *context;
        GdmSessionWorker *worker;
        const char       *address;
        gboolean          is_for_reauth;
        static GOptionEntry entries []   = {
                { NULL }
        };

        bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);
        textdomain (GETTEXT_PACKAGE);
        setlocale (LC_ALL, "");


        context = g_option_context_new (_("GNOME Display Manager Session Worker"));
        g_option_context_add_main_entries (context, entries, NULL);

        g_option_context_parse (context, &argc, &argv, NULL);
        g_option_context_free (context);

        gdm_log_init ();

        settings = gdm_settings_new ();
        if (settings == NULL) {
                g_warning ("Unable to initialize settings");
                exit (1);
        }

        if (! gdm_settings_direct_init (settings, DATADIR "/gdm/gdm.schemas", "/")) {
                g_warning ("Unable to initialize settings");
                exit (1);
        }

        gdm_log_set_debug (is_debug_set ());

        address = g_getenv ("GDM_SESSION_DBUS_ADDRESS");
        if (address == NULL) {
                g_warning ("GDM_SESSION_DBUS_ADDRESS not set");
                exit (1);
        }

        is_for_reauth = g_getenv ("GDM_SESSION_FOR_REAUTH") != NULL;

        worker = gdm_session_worker_new (address, is_for_reauth);

        main_loop = g_main_loop_new (NULL, FALSE);

        g_unix_signal_add (SIGTERM, on_shutdown_signal_cb, main_loop);
        g_unix_signal_add (SIGINT, on_shutdown_signal_cb, main_loop);
        g_unix_signal_add (SIGUSR1, on_sigusr1_cb, NULL);

        g_main_loop_run (main_loop);

        if (worker != NULL) {
                g_object_unref (worker);
        }

        g_main_loop_unref (main_loop);

        g_debug ("Worker finished");

        return 0;
}
