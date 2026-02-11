get_file_list_done (GError   *error,
		    gpointer  user_data)
{
	GetFileListData *gfl = user_data;
	GHashTable      *h_dirs;
	GList           *scan;

	gfl->files = g_list_reverse (gfl->files);
	gfl->dirs = g_list_reverse (gfl->dirs);

	if (! filter_empty (gfl->include_filter) || (gfl->exclude_filter->pattern != NULL)) {
		_g_string_list_free (gfl->dirs);
		gfl->dirs = NULL;
	}

	h_dirs = g_hash_table_new (g_str_hash, g_str_equal);


	if (gfl->base_dir != NULL) {
		char *dir;

		dir = g_strdup (gfl->base_dir);
		gfl->dirs = g_list_prepend (gfl->dirs, dir);
		g_hash_table_insert (h_dirs, dir, GINT_TO_POINTER (1));
	}


	for (scan = gfl->dirs; scan; scan = scan->next)
		g_hash_table_insert (h_dirs, (char*)scan->data, GINT_TO_POINTER (1));

	gfl->dirs = g_list_concat (gfl->dirs, get_dir_list_from_file_list (h_dirs, gfl->base_dir, gfl->files, FALSE));

	if (filter_empty (gfl->include_filter))
		gfl->dirs = g_list_concat (gfl->dirs, get_dir_list_from_file_list (h_dirs, gfl->base_dir, gfl->dirs, TRUE));


	if (error == NULL) {
		GList *rel_files, *rel_dirs;

		if (gfl->base_dir != NULL) {
			rel_files = get_relative_file_list (NULL, gfl->files, gfl->base_dir);
			rel_dirs = get_relative_file_list (NULL, gfl->dirs, gfl->base_dir);
		}
		else {
			rel_files = gfl->files;
			rel_dirs = gfl->dirs;
			gfl->files = NULL;
			gfl->dirs = NULL;
		}


		gfl->done_func (rel_files, rel_dirs, NULL, gfl->done_data);
	}
	else
		gfl->done_func (NULL, NULL, error, gfl->done_data);

	g_hash_table_destroy (h_dirs);
	get_file_list_data_free (gfl);
}
