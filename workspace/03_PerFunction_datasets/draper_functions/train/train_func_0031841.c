prefs_create_autostart_user_file()
{
	GFile *f;
	GError *err = NULL;
	gchar *filename;


	f = g_file_get_parent (autostart_user_file);
	if (!g_file_query_exists (f, NULL)) {
		g_debug ("Preferences: creating user autostart dir...");
		if (!g_file_make_directory_with_parents (f, NULL, &err)) {
			filename = g_file_get_path (f);
			g_warning ("Preferences: Could not mkdir '%s': %s", filename, err->message);
			g_free (filename);
			g_object_unref (f);
			return FALSE;
		}
	}


	filename = g_build_filename (ALARM_CLOCK_DATADIR, "applications", PACKAGE ".desktop", NULL);
	f = g_file_new_for_path (filename);

	if (!g_file_copy (f, autostart_user_file, G_FILE_COPY_NONE, NULL, NULL, NULL, &err)) {
		g_warning ("Preferences: Could not copy '%s' to user config dir: %s", filename, err->message);
		g_error_free (err);
		err = NULL;
		g_free (filename);
		return FALSE;
	}

	g_free (filename);

	return TRUE;
}
