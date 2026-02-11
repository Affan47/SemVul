main (int    argc,
      char **argv)
{
        GError *error = NULL;
        char   *nolock_reason = NULL;

#ifdef ENABLE_NLS
        bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);
# ifdef HAVE_BIND_TEXTDOMAIN_CODESET
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
# endif
        textdomain (GETTEXT_PACKAGE);
#endif

        if (! g_thread_supported ()) {
                g_thread_init (NULL);
        }

        g_type_init ();

        gs_profile_start (NULL);

        if (! privileged_initialization (&argc, argv, verbose)) {
                response_lock_init_failed ();
                exit (1);
        }

        error = NULL;
        if (! gtk_init_with_args (&argc, &argv, NULL, entries, NULL, &error)) {
                if (error != NULL) {
                        fprintf (stderr, "%s", error->message);
                        g_error_free (error);
                }
                exit (1);
        }

        if (show_version) {
                g_print ("%s %s\n", argv [0], VERSION);
                exit (1);
        }

        if (! lock_initialization (&argc, argv, &nolock_reason, verbose)) {
                if (nolock_reason != NULL) {
                        g_debug ("Screen locking disabled: %s", nolock_reason);
                        g_free (nolock_reason);
                }
                response_lock_init_failed ();
                exit (1);
        }

        gs_debug_init (verbose, FALSE);

        g_idle_add ((GSourceFunc)popup_dialog_idle, NULL);

        gtk_main ();

        gs_profile_end (NULL);
        gs_debug_shutdown ();

        return 0;
}
