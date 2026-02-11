gpk_desktop_guess_localised_name (PkDesktop *desktop, const gchar *package)
{
	GKeyFile *file;
	gchar *filename;
	gchar *data = NULL;
	gboolean ret;

	filename = gpk_desktop_guess_best_file (desktop, package);
	if (filename == NULL)
		goto out;


	file = g_key_file_new ();
	ret = g_key_file_load_from_file (file, filename, G_KEY_FILE_KEEP_TRANSLATIONS, NULL);
	if (!ret) {
		g_warning ("failed to open %s", filename);
		goto out;
	}
	data = g_key_file_get_string (file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL);
	g_key_file_free (file);
out:
	g_free (filename);
	return data;
}
