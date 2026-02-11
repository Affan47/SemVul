config_finalize (GObject *object)
{
	TrackerConfigFile *file;
	TrackerConfigFilePrivate *priv;

	file = TRACKER_CONFIG_FILE (object);
	priv = TRACKER_CONFIG_FILE_GET_PRIVATE (file);

	if (file->key_file) {
		g_key_file_free (file->key_file);
	}

	if (file->monitor) {
		g_file_monitor_cancel (file->monitor);
		g_object_unref (file->monitor);
	}

	if (file->file) {
		g_object_unref (file->file);
	}

	g_free (priv->domain);

	(G_OBJECT_CLASS (tracker_config_file_parent_class)->finalize) (object);
}
