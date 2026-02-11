_g_copy_file_to_destination (CopyFileData   *copy_file_data,
			     GFile          *destination,
			     GFileCopyFlags  flags)
{
	_g_object_unref (copy_file_data->current_destination);
	copy_file_data->current_destination = g_file_dup (destination);

	if (copy_file_data->default_response == GTH_OVERWRITE_RESPONSE_ALWAYS_YES)
		flags = G_FILE_COPY_OVERWRITE;

	if (copy_file_data->progress_callback != NULL) {
		GFile *destination_parent;
		char  *destination_name;

		g_free (copy_file_data->message);

		destination_parent = g_file_get_parent (copy_file_data->current_destination);
		destination_name = g_file_get_parse_name (destination_parent);
		if (copy_file_data->move)
			copy_file_data->message = g_strdup_printf (_("Moving \"%s\" to \"%s\""), g_file_info_get_display_name (copy_file_data->source->info), destination_name);
		else
			copy_file_data->message = g_strdup_printf (_("Copying \"%s\" to \"%s\""), g_file_info_get_display_name (copy_file_data->source->info), destination_name);

		copy_file_progress_cb (0, 0, copy_file_data);

		g_free (destination_name);
		g_object_unref (destination_parent);
	}

	if (g_file_info_get_file_type (copy_file_data->source->info) == G_FILE_TYPE_DIRECTORY) {
		GError *error = NULL;

		if (! g_file_make_directory (copy_file_data->current_destination, copy_file_data->cancellable, &error)) {
			if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_EXISTS))
				g_clear_error (&error);
		}
		copy_file_data->ready_callback (copy_file_data->default_response, error, copy_file_data->user_data);
		copy_file_data_free (copy_file_data);
		return;
	}
	else
		g_file_copy_async (copy_file_data->source->file,
				   copy_file_data->current_destination,
				   copy_file_data->flags | flags,
				   copy_file_data->io_priority,
				   copy_file_data->cancellable,
				   copy_file_progress_cb,
				   copy_file_data,
				   copy_file_ready_cb,
				   copy_file_data);
}
