brasero_image_format_cue_bin_byte_swap (gchar *uri,
					GCancellable *cancel,
					GError **error)
{
	GFile *file;
	gchar *line;
	GFileInputStream *input;
	GDataInputStream *stream;
	gboolean is_audio = FALSE;
	gboolean is_binary = FALSE;

	file = g_file_new_for_uri (uri);
	input = g_file_read (file, cancel, error);

	if (!input) {
		g_object_unref (file);
		return FALSE;
	}

	stream = g_data_input_stream_new (G_INPUT_STREAM (input));
	g_object_unref (input);

	while ((line = g_data_input_stream_read_line (stream, NULL, cancel, error))) {
		const gchar *ptr;

		if ((ptr = strstr (line, "FILE"))) {
			if (strstr (ptr, "BINARY"))
				is_binary = TRUE;
		}
		else if ((ptr = strstr (line, "TRACK"))) {
			if (strstr (ptr, "AUDIO"))
				is_audio = TRUE;
		}
		g_free (line);
	}

	g_object_unref (stream);
	g_object_unref (file);

	return is_binary && is_audio;
}
