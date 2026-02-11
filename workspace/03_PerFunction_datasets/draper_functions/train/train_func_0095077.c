main(int argc, char *argv[])
{
	GOptionContext *context;
	GError *error = NULL;
	textdomain (GETTEXT_PACKAGE);

	gtk_init (&argc, &argv);
	gcu::Element::Init ();
	App = new gcpStandaloneApp();
	if (argc > 1 && argv[1][0] == '-') {
		context = g_option_context_new (_(" [file...]"));
		g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);
		App->AddOptions (context);
		g_option_context_add_group (context, gtk_get_option_group (TRUE));
		g_option_context_set_help_enabled (context, TRUE);
		g_option_context_parse (context, &argc, &argv, &error);
		if (error) {
			puts (error->message);
			g_error_free (error);
			return -1;
		}
	}
	argv ++;
	argc --;

	char *path, *uri;
	while (*argv) {
		if (**argv == '-') {
			printf (_("Invalid or misplaced argument: %s\n"), *argv);
			delete App;
			exit (-1);
		}
		if (strstr (*argv, "://"))
			uri = g_strdup (*argv);
		else {
			if (g_path_is_absolute (*argv))
				path = g_strdup (*argv);
			else {
				char *dir = g_get_current_dir ();
				path = g_build_filename (dir, *argv, NULL);
				g_free (dir);
			}
			uri = g_filename_to_uri (path, NULL, NULL);
			g_free (path);
		}
		char *mime_type = go_get_mime_type (uri);
		App->FileProcess (uri, mime_type, false, NULL, NULL);
		g_free (mime_type);
		g_free (uri);
		argv++;
	}

	if (App->GetDocsNumber () == 0)
		App->OnFileNew ();


	struct sigaction sa;
	sa.sa_handler = signalWrapper;

	sigfillset (&sa.sa_mask);
	sigdelset (&sa.sa_mask, SIGABRT);
#if defined (SA_NODEFER) && defined (SA_RESETHAND)
	sa.sa_flags = SA_NODEFER | SA_RESETHAND;
#else
	sa.sa_flags = 0;
#endif

	sigaction (SIGSEGV, &sa, NULL);
	sigaction (SIGBUS, &sa, NULL);
	sigaction (SIGILL, &sa, NULL);
	sigaction (SIGQUIT, &sa, NULL);
	sigaction (SIGFPE, &sa, NULL);


	gtk_main ();
	delete App;

	return 0;
}
