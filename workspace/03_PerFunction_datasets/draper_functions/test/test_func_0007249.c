main (int argc,
      char **argv)
{
        GUPnPDLNAProfileGuesser *guesser;
        gboolean relaxed_mode = FALSE;
        gboolean extended_mode = FALSE;
        GError *err = NULL;

        GOptionEntry options[] = {
                {"timeout", 't', 0, G_OPTION_ARG_INT, &timeout,
                 "Specify timeout (in seconds, defaults to 10)", "T"},
                {"async", 'a', 0, G_OPTION_ARG_NONE, &async,
                 "Run asynchronously", NULL},
                {"relaxed mode", 'r', 0, G_OPTION_ARG_NONE, &relaxed_mode,
                 "Enable Relaxed mode", NULL},
                {"extended mode", 'e', 0, G_OPTION_ARG_NONE, &extended_mode,
                 "Enable extended mode", NULL},
                {NULL}
        };

        GOptionContext *ctx;

#if !GLIB_CHECK_VERSION(2,35,0)
        g_type_init ();
#endif

        ctx = g_option_context_new (" - program to extract DLNA and related metadata");
        g_option_context_add_main_entries (ctx, options, NULL);

        if (!g_option_context_parse (ctx, &argc, &argv, &err)) {

                g_print ("Error initializing: %s\n", err->message);
                g_error_free (err);
                exit (1);
        }

        g_option_context_free (ctx);

        if (argc < 2) {
                g_print ("usage:%s <files>\n", argv[0]);
                return -1;
        }


        timeout *= 1000;

        guesser = gupnp_dlna_profile_guesser_new (relaxed_mode,
                                                  extended_mode);

        if (async == FALSE) {
                gint iter;

                for (iter = 1; iter < argc; ++iter)
                        process_file (guesser, argv[iter]);
        } else {
                PrivStruct *ps = g_slice_new0 (PrivStruct);
                GMainLoop *ml = g_main_loop_new (NULL, FALSE);

                ps->guesser = guesser;
                ps->argc = argc;
                ps->argv = argv;

                g_idle_add ((GSourceFunc) async_idle_loop, ps);

                g_signal_connect (guesser, "done",
                                  G_CALLBACK (guesser_done), ml);

                g_main_loop_run (ml);
                g_main_loop_unref (ml);
                g_slice_free (PrivStruct, ps);
        }
        g_object_unref (guesser);
        gupnp_dlna_profile_guesser_cleanup ();
        return 0;
}
