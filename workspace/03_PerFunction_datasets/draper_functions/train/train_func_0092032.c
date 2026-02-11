fr_archive_add_files_with_filter (FrArchive           *archive,
				  GList               *file_list,
				  GFile               *source_dir,
				  const char          *include_files,
				  const char          *exclude_files,
				  const char          *exclude_directories,
				  const char          *dest_dir,
				  gboolean             update,
				  gboolean             follow_links,
				  const char          *password,
				  gboolean             encrypt_header,
				  FrCompression        compression,
				  guint                volume_size,
				  GCancellable        *cancellable,
				  GAsyncReadyCallback  callback,
				  gpointer             user_data)
{
	AddData       *add_data;
	FileListFlags  flags;

	g_return_if_fail (! archive->read_only);

	add_data = g_new0 (AddData, 1);
	add_data->archive = archive;
	add_data->base_dir = _g_object_ref (source_dir);
	add_data->dest_dir = g_strdup (dest_dir);
	add_data->update = update;
	add_data->follow_links = follow_links;
	add_data->password = g_strdup (password);
	add_data->encrypt_header = encrypt_header;
	add_data->compression = compression;
	add_data->volume_size = volume_size;
	add_data->cancellable = _g_object_ref (cancellable);
	add_data->callback = callback;
	add_data->user_data = user_data;
	add_data->include_files_filter = file_filter_new (include_files);
	add_data->exclude_files_filter = file_filter_new (exclude_files);
	add_data->exclude_directories_filter = file_filter_new (exclude_directories);

	fr_archive_action_started (archive, FR_ACTION_GETTING_FILE_LIST);

	flags = FILE_LIST_RECURSIVE | FILE_LIST_NO_BACKUP_FILES;
	if (! follow_links)
		flags |= FILE_LIST_NO_FOLLOW_LINKS;
	_g_file_list_query_info_async (file_list,
				       flags,
				       (G_FILE_ATTRIBUTE_STANDARD_NAME ","
					G_FILE_ATTRIBUTE_STANDARD_SIZE ","
					G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN ","
					G_FILE_ATTRIBUTE_STANDARD_IS_BACKUP),
				       cancellable,
				       directory_filter_cb,
				       file_filter_cb,
				       fr_archive_add_files_ready_cb,
				       add_data);
}
