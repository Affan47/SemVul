go_plugins_shutdown (void)
{
	GSList *used_plugin_state_strings = NULL;
	GOErrorInfo *ignored_error;

	if (plugins_marked_for_deactivation_hash != NULL) {
		g_hash_table_destroy (plugins_marked_for_deactivation_hash);
	}


	go_plugin_db_deactivate_plugin_list (available_plugins, &ignored_error);
	go_error_info_free (ignored_error);


	g_hash_table_foreach (
		plugin_file_state_dir_hash,
		ghf_collect_used_plugin_state_strings,
		&used_plugin_state_strings);
	if (!plugin_file_state_hash_changed &&
	    g_hash_table_size (plugin_file_state_dir_hash) == g_slist_length (used_plugin_state_strings)) {
		g_slist_free_full (used_plugin_state_strings, g_free);
		used_plugin_state_strings = NULL;
	}

	g_hash_table_destroy (plugin_file_state_dir_hash);
	g_hash_table_destroy (loader_services);
	g_hash_table_destroy (available_plugins_id_hash);
	g_slist_free_full (available_plugins, g_object_unref);

	if (go_plugin_dirs) {
		g_slist_foreach (go_plugin_dirs, (GFunc) g_free, NULL);
		g_slist_free (go_plugin_dirs);
		go_plugin_dirs = NULL;
	}

	return used_plugin_state_strings;
}
