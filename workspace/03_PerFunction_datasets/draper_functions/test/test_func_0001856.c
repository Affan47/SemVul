save_to_buffer_ready_cb (GObject      *source_object,
			 GAsyncResult *result,
			 gpointer      user_data)
{
	SaveArguments    *arguments = user_data;
	GthImageSaveData *data = NULL;
	GError           *error = NULL;
	GthImageSaveFile *file;

	if (! gth_image_save_to_buffer_finish (result, &data, &error)) {
		gth_file_data_ready_with_error (arguments->file_data,
						arguments->ready_func,
						arguments->user_data,
						error);
		save_arguments_free (arguments);
		return;
	}

	data->replace = arguments->replace;

	file = g_new0 (GthImageSaveFile, 1);
	file->file = g_object_ref (data->file_data->file);
	file->buffer = data->buffer;
	file->buffer_size = data->buffer_size;
	data->files = g_list_prepend (data->files, file);

	save_files (data, arguments->ready_func, arguments->user_data);

	save_arguments_free (arguments);
}
