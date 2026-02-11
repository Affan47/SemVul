report_statistics (GObject *object)
{
	TrackerExtractPrivate *priv;
	GHashTableIter iter;
	gpointer key, value;

	priv = TRACKER_EXTRACT_GET_PRIVATE (object);

#if GLIB_CHECK_VERSION (2,31,0)
	g_mutex_lock (&priv->task_mutex);
#else
	g_mutex_lock (priv->task_mutex);
#endif

	g_message ("--------------------------------------------------");
	g_message ("Statistics:");

	g_hash_table_iter_init (&iter, priv->statistics_data);

	while (g_hash_table_iter_next (&iter, &key, &value)) {
		GModule *module = key;
		StatisticsData *data = value;

		if (data->extracted_count > 0 || data->failed_count > 0) {
			const gchar *name, *name_without_path;

			name = g_module_name (module);
			name_without_path = strrchr (name, G_DIR_SEPARATOR) + 1;

			g_message ("    Module:'%s', extracted:%d, failures:%d",
			           name_without_path,
			           data->extracted_count,
			           data->failed_count);
		}
	}

	g_message ("Unhandled files: %d", priv->unhandled_count);

	if (priv->unhandled_count == 0 &&
	    g_hash_table_size (priv->statistics_data) < 1) {
		g_message ("    No files handled");
	}

	g_message ("--------------------------------------------------");

#if GLIB_CHECK_VERSION (2,31,0)
	g_mutex_unlock (&priv->task_mutex);
#else
	g_mutex_unlock (priv->task_mutex);
#endif
}
