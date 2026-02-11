load_password_file (TrackerPasswordProviderKeyfile  *kf,
                    GError                         **error)
{
	TrackerPasswordProviderKeyfilePrivate *priv;
	GError *inner_error = NULL;
	gchar *filename;
	gchar *directory;

	directory = config_dir_ensure_exists_and_return (error);
	if (!directory) {
		return FALSE;
	}

	filename = g_build_filename (directory, KEYFILE_FILENAME, NULL);
	g_free (directory);

	priv = TRACKER_PASSWORD_PROVIDER_KEYFILE_GET_PRIVATE (kf);

	g_key_file_load_from_file (priv->password_file,
	                           filename,
	                           G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS,
	                           &inner_error);

	if (inner_error) {
		g_critical ("Could not load GKeyFile password file '%s', %s",
		            filename,
		            inner_error->message);
		g_propagate_error (error, inner_error);
		g_free (filename);

		return FALSE;
	}

	g_free (filename);

	return TRUE;
}
