startup_data_new (GList *original_files,
		  GList *target_files,
		  const char *pending_key,
		  GtkWidget *parent_widget,
		  const char *startup_id)
{
	StartupData *data;
	GList *l;

	data = g_new0 (StartupData, 1);
	data->original_files = nautilus_file_list_copy (original_files);
	data->target_files = nautilus_file_list_copy (target_files);
	data->parent_widget = parent_widget;
	data->startup_id = g_strdup (startup_id);
	data->pending_key = g_strdup (pending_key);
	data->pending_files = g_hash_table_new (g_direct_hash,
						g_direct_equal);

	for (l = data->target_files; l != NULL; l = l->next) {
		g_hash_table_insert (data->pending_files, l->data, l->data);
	}

	return data;
}
