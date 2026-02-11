remove_leftovers (CopyOneSettingValueInfo *info)
{
	GSList *dirs;
	GSList *iter;
	size_t prefix_len;

	prefix_len = strlen (info->dir) + 1;

	dirs = gconf_client_all_dirs (info->client, info->dir, NULL);
	for (iter = dirs; iter; iter = iter->next) {
		char *key = (char *) iter->data;
		NMSetting *setting;

		setting = nm_connection_get_setting_by_name (info->connection, key + prefix_len);
		if (!setting)
			gconf_client_recursive_unset (info->client, key, 0, NULL);

		g_free (key);
	}

	g_slist_free (dirs);
}
