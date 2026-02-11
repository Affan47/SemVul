do_scriptdir (const gchar *scriptdir, const gchar *arg1)
{
	GError *err = NULL;
	GDir *dir;
	const gchar *f;
	gchar *argv[3] = {NULL, NULL, NULL};

	XMMS_DBG ("Running scripts in %s", scriptdir);
	if (!g_file_test (scriptdir, G_FILE_TEST_IS_DIR)) {
		g_mkdir_with_parents (scriptdir, 0755);
		install_scripts (scriptdir);
	}

	dir = g_dir_open (scriptdir, 0, &err);
	if (!dir) {
		xmms_log_error ("Could not open script dir '%s' error: %s", scriptdir, err->message);
		return;
	}

	argv[1] = g_strdup (arg1);
	while ((f = g_dir_read_name (dir))) {
		argv[0] = g_strdup_printf ("%s/%s", scriptdir, f);
		if (g_file_test (argv[0], G_FILE_TEST_IS_EXECUTABLE)) {
			if (!g_spawn_async (g_get_home_dir (), argv, NULL, 0,
			                    spawn_script_setup, NULL, NULL, &err)) {
				xmms_log_error ("Could not run script '%s', error: %s",
				                argv[0], err->message);
			}
		}
		g_free (argv[0]);
	}
	g_free (argv[1]);

	g_dir_close (dir);

}
