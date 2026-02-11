prefs_filtering_clear(void)
{
	GList * cur;

	for (cur = folder_get_list() ; cur != NULL ; cur = g_list_next(cur)) {
		Folder *folder;

		folder = (Folder *) cur->data;
		g_node_traverse(folder->node, G_PRE_ORDER, G_TRAVERSE_ALL, -1,
				prefs_filtering_free_func, NULL);
	}

	prefs_filtering_free(filtering_rules);
	filtering_rules = NULL;
	prefs_filtering_free(pre_global_processing);
	pre_global_processing = NULL;
	prefs_filtering_free(post_global_processing);
	post_global_processing = NULL;
}
