config_load (TrackerConfigFile *file)
{
	TrackerConfigFilePrivate *priv;
	GError *error = NULL;
	gchar *basename;
	gchar *filename;
	gchar *directory;


	directory = config_dir_ensure_exists_and_return ();
	if (!directory) {
		return;
	}

	priv = TRACKER_CONFIG_FILE_GET_PRIVATE (file);

	basename = g_strdup_printf ("%s.cfg", priv->domain);
	filename = g_build_filename (directory, basename, NULL);
	g_free (basename);
	g_free (directory);


	if (!file->file) {
		file->file = g_file_new_for_path (filename);
	}

	if (!file->monitor) {
		file->monitor = g_file_monitor_file (file->file,
		                                     G_FILE_MONITOR_NONE,
		                                     NULL,
		                                     NULL);

		g_signal_connect (file->monitor, "changed",
		                  G_CALLBACK (config_changed_cb),
		                  file);
	}


	g_key_file_load_from_file (file->key_file,
	                           filename,
	                           G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS,
	                           &error);


	file->file_exists = error ? FALSE : TRUE;

	if (error) {
		g_error_free (error);
	}

	g_free (filename);
}
