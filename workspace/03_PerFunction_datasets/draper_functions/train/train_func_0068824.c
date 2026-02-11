cd_profile_store_file_monitor_changed_cb (GFileMonitor *monitor,
					  GFile *file, GFile *other_file,
					  GFileMonitorEvent event_type,
					  CdProfileStore *profile_store)
{
	gboolean ret;
	gchar *parent_path = NULL;
	gchar *path = NULL;
	GFile *parent = NULL;


	if (event_type != G_FILE_MONITOR_EVENT_CREATED)
		goto out;


	path = g_file_get_path (file);
	if (g_strrstr (path, ".goutputstream") != NULL) {
		g_debug ("CdProfileStore: ignoring gvfs temporary file");
		goto out;
	}


	parent = g_file_get_parent (file);
	parent_path = g_file_get_path (parent);
	if (g_strcmp0 (parent_path, DATADIR) == 0) {
		g_debug ("CdProfileStore: %s was added, rescanning", path);
		ret = cd_profile_store_search_path (profile_store, path);
		if (!ret)
			g_debug ("CdProfileStore: no new profiles found in %s", path);
	} else {
		g_debug ("CdProfileStore: %s was added, rescanning parent %s",
			 path, parent_path);
		ret = cd_profile_store_search_path (profile_store, parent_path);
		if (!ret)
			g_debug ("CdProfileStore: no new profiles found in %s", parent_path);
	}
out:
	if (parent != NULL)
		g_object_unref (parent);
	g_free (path);
	g_free (parent_path);
}
