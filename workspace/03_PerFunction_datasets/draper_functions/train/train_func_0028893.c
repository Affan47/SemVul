get_desktop_key_file (GFile   *file,
                      gchar  **type,
                      GError **error)
{
	GKeyFile *key_file;
	gchar *path;
	gchar *str;

	path = g_file_get_path (file);
	key_file = g_key_file_new ();
	*type = NULL;

	if (!g_key_file_load_from_file (key_file, path, G_KEY_FILE_NONE, NULL)) {
		g_set_error (error, miner_applications_error_quark, 0, "Couldn't load desktop file:'%s'", path);
		g_key_file_free (key_file);
		g_free (path);
		return NULL;
	}

	str = g_key_file_get_string (key_file, GROUP_DESKTOP_ENTRY, "Type", NULL);

	if (G_UNLIKELY (!str)) {
		*type = NULL;

		g_set_error_literal (error, miner_applications_error_quark, 0, "Desktop file doesn't contain type");
		g_key_file_free (key_file);
		g_free (path);
		return NULL;
	} else {

		*type = g_strstrip (str);
	}

	g_free (path);

	return key_file;
}
