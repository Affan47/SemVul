go_plugin_list_read_for_subdirs_of_dir (gchar const *dir_name, GOErrorInfo **ret_error)
{
	GSList *plugins = NULL;
	GDir *dir;
	char const *d_name;
	GSList *error_list = NULL;

	g_return_val_if_fail (dir_name != NULL, NULL);

	GO_INIT_RET_ERROR_INFO (ret_error);
	dir = g_dir_open (dir_name, 0, NULL);
	if (dir == NULL)
		return NULL;

	while ((d_name = g_dir_read_name (dir)) != NULL) {
		gchar *full_entry_name;
		GOErrorInfo *error = NULL;
		GOPlugin *plugin;

		if (strcmp (d_name, ".") == 0 || strcmp (d_name, "..") == 0)
			continue;
		full_entry_name = g_build_filename (dir_name, d_name, NULL);
		plugin = go_plugin_read_for_dir (full_entry_name, &error);
		if (plugin != NULL) {
			GO_SLIST_PREPEND (plugins, plugin);
		}
		if (error != NULL) {
			GO_SLIST_PREPEND (error_list, error);
		}
		g_free (full_entry_name);
	}
	if (error_list != NULL) {
		GO_SLIST_REVERSE (error_list);
		*ret_error = go_error_info_new_from_error_list (error_list);
	}
	g_dir_close (dir);

	return g_slist_reverse (plugins);
}
