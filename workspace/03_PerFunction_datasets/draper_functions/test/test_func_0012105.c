query_data__start_dir_cb (GFile       *file,
		          GFileInfo   *info,
		          GError     **error,
		          gpointer     user_data)
{
	QueryData *query_data = user_data;

	if ((query_data->flags & FILE_LIST_NO_BACKUP_FILES) && g_file_info_get_is_backup (info))
		return DIR_OP_SKIP;
	if ((query_data->flags & FILE_LIST_NO_HIDDEN_FILES) && g_file_info_get_is_hidden (info))
		return DIR_OP_SKIP;
	if ((query_data->directory_filter_func != NULL) && query_data->directory_filter_func (file, info, query_data->user_data))
		return DIR_OP_SKIP;

	query_data->files = g_list_prepend (query_data->files, file_info_new (file, info));

	return DIR_OP_CONTINUE;
}
