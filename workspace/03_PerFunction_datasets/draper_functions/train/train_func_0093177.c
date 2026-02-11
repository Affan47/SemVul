snippets_load(GKeyFile *sysconfig, GKeyFile *userconfig)
{
	gsize i, j, len = 0, len_keys = 0;
	gchar **groups_user, **groups_sys;
	gchar **keys_user, **keys_sys;
	gchar *value;
	GHashTable *tmp;


	snippet_hash =
		g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify) g_hash_table_destroy);


	groups_sys = g_key_file_get_groups(sysconfig, &len);
	for (i = 0; i < len; i++)
	{
		if (strcmp(groups_sys[i], "Keybindings") == 0)
			continue;
		keys_sys = g_key_file_get_keys(sysconfig, groups_sys[i], &len_keys, NULL);

		tmp = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
		g_hash_table_insert(snippet_hash, g_strdup(groups_sys[i]), tmp);

		for (j = 0; j < len_keys; j++)
		{
			g_hash_table_insert(tmp, g_strdup(keys_sys[j]),
						utils_get_setting_string(sysconfig, groups_sys[i], keys_sys[j], ""));
		}
		g_strfreev(keys_sys);
	}
	g_strfreev(groups_sys);


	groups_user = g_key_file_get_groups(userconfig, &len);
	for (i = 0; i < len; i++)
	{
		if (strcmp(groups_user[i], "Keybindings") == 0)
			continue;
		keys_user = g_key_file_get_keys(userconfig, groups_user[i], &len_keys, NULL);

		tmp = g_hash_table_lookup(snippet_hash, groups_user[i]);
		if (tmp == NULL)
		{
			tmp = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
			g_hash_table_insert(snippet_hash, g_strdup(groups_user[i]), tmp);
		}
		for (j = 0; j < len_keys; j++)
		{
			value = g_hash_table_lookup(tmp, keys_user[j]);
			if (value == NULL)
			{
				g_hash_table_insert(tmp, g_strdup(keys_user[j]),
						utils_get_setting_string(userconfig, groups_user[i], keys_user[j], ""));
			}
			else
			{
				g_hash_table_replace(tmp, g_strdup(keys_user[j]),
						utils_get_setting_string(userconfig, groups_user[i], keys_user[j], ""));
			}
		}
		g_strfreev(keys_user);
	}
	g_strfreev(groups_user);
}
