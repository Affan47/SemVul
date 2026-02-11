main (int argc, char *argv[])
{
	int status;

	program_argv0 = argv[0];

	g_type_init ();


	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);


	Main_Application = gth_application_new ();
	status = g_application_run (G_APPLICATION (Main_Application), argc, argv);

	gth_main_release ();
	gth_pref_release ();
	g_object_unref (Main_Application);


	if (Restart)
		g_spawn_command_line_async (program_argv0, NULL);

	return status;
}
