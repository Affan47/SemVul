fr_command_add_files (FrArchive           *base,
		      GList               *file_list,
		      GFile               *base_dir,
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
	FrCommand          *self = FR_COMMAND (base);
	GSimpleAsyncResult *result;

	result = g_simple_async_result_new (G_OBJECT (self),
					    callback,
					    user_data,
					    fr_archive_add_files);

	if (_g_file_is_local (base_dir))
		_fr_command_add_local_files (self,
					     file_list,
					     base_dir,
					     dest_dir,
					     update,
					     follow_links,
					     password,
					     encrypt_header,
					     compression,
					     volume_size,
					     cancellable,
					     result);
	else
		copy_remote_files (self,
				   file_list,
				   base_dir,
				   dest_dir,
				   update,
				   follow_links,
				   password,
				   encrypt_header,
				   compression,
				   volume_size,
				   _fr_command_get_temp_work_dir (self),
				   cancellable,
				   result);
}
