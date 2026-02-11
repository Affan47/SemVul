brasero_io_image_directory_contents_thread (BraseroAsyncTaskManager *manager,
					    GCancellable *cancel,
					    gpointer callback_data)
{
	BraseroIOImageContentsData *data = callback_data;
	BraseroDeviceHandle *handle;
	GList *children, *iter;
	GError *error = NULL;
	BraseroVolSrc *vol;

	handle = brasero_device_handle_open (data->job.uri, FALSE, NULL);
	if (!handle) {
		GError *error;

		error = g_error_new (BRASERO_BURN_ERROR,
		                     BRASERO_BURN_ERROR_GENERAL,
		                     _("The drive is busy"));

		brasero_io_return_result (data->job.base,
					  data->job.uri,
					  NULL,
					  error,
					  data->job.callback_data);
		return BRASERO_ASYNC_TASK_FINISHED;
	}

	vol = brasero_volume_source_open_device_handle (handle, &error);
	if (!vol) {
		brasero_device_handle_close (handle);
		brasero_io_return_result (data->job.base,
					  data->job.uri,
					  NULL,
					  error,
					  data->job.callback_data);
		return BRASERO_ASYNC_TASK_FINISHED;
	}

	children = brasero_volume_load_directory_contents (vol,
							   data->session_block,
							   data->block,
							   &error);
	brasero_volume_source_close (vol);
	brasero_device_handle_close (handle);

	for (iter = children; iter; iter = iter->next) {
		BraseroVolFile *file;
		GFileInfo *info;

		file = iter->data;

		info = g_file_info_new ();
		g_file_info_set_file_type (info, file->isdir? G_FILE_TYPE_DIRECTORY:G_FILE_TYPE_REGULAR);
		g_file_info_set_name (info, BRASERO_VOLUME_FILE_NAME (file));

		if (file->isdir)
			g_file_info_set_attribute_int64 (info,
							 BRASERO_IO_DIR_CONTENTS_ADDR,
							 file->specific.dir.address);
		else
			g_file_info_set_size (info, BRASERO_VOLUME_FILE_SIZE (file));

		brasero_io_return_result (data->job.base,
					  data->job.uri,
					  info,
					  NULL,
					  data->job.callback_data);
	}

	g_list_foreach (children, (GFunc) brasero_volume_file_free, NULL);
	g_list_free (children);

	return BRASERO_ASYNC_TASK_FINISHED;
}
