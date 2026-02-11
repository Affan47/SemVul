applets_directory_changed (GFileMonitor     *monitor,
			   GFile            *file,
			   GFile            *other_file,
			   GFileMonitorEvent event_type,
			   gpointer          user_data)
{
	PanelAppletsManagerDBus *manager = PANEL_APPLETS_MANAGER_DBUS (user_data);

	switch (event_type) {
	case G_FILE_MONITOR_EVENT_CHANGED:
	case G_FILE_MONITOR_EVENT_CREATED: {
		PanelAppletFactoryInfo *info;
		PanelAppletFactoryInfo *old_info;
		gchar                  *filename;
		GSList                 *dirs, *d;

		filename = g_file_get_path (file);
		if (!g_str_has_suffix (filename, PANEL_APPLETS_EXTENSION)) {
			g_free (filename);
			return;
		}

		info = panel_applets_manager_get_applet_factory_info_from_file (filename);
		g_free (filename);

		if (!info)
			return;

		old_info = g_hash_table_lookup (manager->priv->applet_factories, info->id);
		if (!old_info) {

			g_hash_table_insert (manager->priv->applet_factories, g_strdup (info->id), info);
			return;
		}


		if (g_strcmp0 (info->srcdir, old_info->srcdir) == 0) {
			g_hash_table_replace (manager->priv->applet_factories, g_strdup (info->id), info);
			return;
		}

		dirs = panel_applets_manager_get_applets_dirs ();

		for (d = dirs; d; d = g_slist_next (d)) {
			gchar *path = (gchar *) d->data;

			if (g_strcmp0 (path, old_info->srcdir) == 0) {
				panel_applet_factory_info_free (info);
				break;
			} else if (g_strcmp0 (path, info->srcdir) == 0) {
				g_hash_table_replace (manager->priv->applet_factories, g_strdup (info->id), info);
				break;
			}
		}

		g_slist_foreach (dirs, (GFunc) g_free, NULL);
		g_slist_free (dirs);
	}
		break;
	default:

		break;
	}
}
