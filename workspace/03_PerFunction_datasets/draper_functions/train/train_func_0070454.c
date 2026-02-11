top_left_read_callback (GObject *source_object,
			GAsyncResult *res,
			gpointer callback_data)
{
	TopLeftTextReadState *state;
	NemoDirectory *directory;
	NemoFileDetails *file_details;
	gsize file_size;
	char *file_contents;

	state = callback_data;

	if (state->directory == NULL) {

		top_left_read_state_free (state);
		return;
	}

	directory = nemo_directory_ref (state->directory);

	file_details = state->file->details;

	file_details->top_left_text_is_up_to_date = TRUE;
	g_free (file_details->top_left_text);

	if (g_file_load_partial_contents_finish (G_FILE (source_object),
						 res,
						 &file_contents, &file_size,
						 NULL, NULL)) {
		file_details->top_left_text = nemo_extract_top_left_text (file_contents, state->large, file_size);
		file_details->got_top_left_text = TRUE;
		file_details->got_large_top_left_text = state->large;
		g_free (file_contents);
	} else {
		file_details->top_left_text = NULL;
		file_details->got_top_left_text = FALSE;
		file_details->got_large_top_left_text = FALSE;
	}

	nemo_file_changed (state->file);

	directory->details->top_left_read_state = NULL;
	async_job_end (directory, "top left");

	top_left_read_state_free (state);

	nemo_directory_async_state_changed (directory);

	nemo_directory_unref (directory);
}
