copy_file__copy_current_sidecar (CopyFileData *copy_file_data)
{
	GFile *source;
	GFile *destination;
	GFile *destination_parent;

	if (copy_file_data->current_source_sidecar == NULL) {
		copy_file__delete_source (copy_file_data);
		return;
	}

	source = copy_file_data->current_source_sidecar->data;
	if (! g_file_query_exists (source, copy_file_data->cancellable)) {
		copy_file__copy_next_sidecar (copy_file_data);
		return;
	}

	destination = copy_file_data->current_destination_sidecar->data;
	destination_parent = g_file_get_parent (destination);
	g_file_make_directory (destination_parent, copy_file_data->cancellable, NULL);

	g_file_copy_async (source,
			   destination,
			   G_FILE_COPY_OVERWRITE,
			   copy_file_data->io_priority,
			   copy_file_data->cancellable,
			   NULL,
			   NULL,
			   copy_file__copy_current_sidecar_ready_cb,
			   copy_file_data);

	g_object_unref (destination_parent);
}
