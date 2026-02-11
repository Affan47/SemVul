get_monitor_file_source_for_file (GthFolderTree *folder_tree,
				  GFile         *file)
{
	GList *scan;
	char  *uri;

	uri = g_file_get_uri (file);
	for (scan = folder_tree->priv->monitor.sources; scan; scan = scan->next) {
		GthFileSource *file_source = scan->data;

		if (gth_file_source_supports_scheme (file_source, uri)) {
			g_free (uri);
			return file_source;
		}
	}

	g_free (uri);

	return NULL;
}
