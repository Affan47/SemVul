for_each_child_compute_child (ForEachChildData *fec,
			      GFile            *file,
			      GFileInfo        *info)
{
	if (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY) {
		char *id;


		id = g_strdup (g_file_info_get_attribute_string (info, G_FILE_ATTRIBUTE_ID_FILE));
		if (id == NULL)
			id = g_file_get_uri (file);

		if (g_hash_table_lookup (fec->already_visited, id) == NULL) {
			g_hash_table_insert (fec->already_visited, g_strdup (id), GINT_TO_POINTER (1));
			fec->to_visit = g_list_append (fec->to_visit, child_data_new (file, info));
		}

		g_free (id);
	}

	fec->for_each_file_func (file, info, fec->user_data);
}
