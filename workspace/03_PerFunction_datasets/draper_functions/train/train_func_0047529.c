check_is_directory (TrackerMonitor *monitor,
                    GFile          *file)
{
	GFileType file_type;

	file_type = g_file_query_file_type (file, G_FILE_QUERY_INFO_NONE, NULL);

	if (file_type == G_FILE_TYPE_DIRECTORY)
		return TRUE;

	if (file_type == G_FILE_TYPE_UNKNOWN) {


		if (g_hash_table_lookup (monitor->priv->monitors, file) != NULL)
			return TRUE;
	}

	return FALSE;
}
