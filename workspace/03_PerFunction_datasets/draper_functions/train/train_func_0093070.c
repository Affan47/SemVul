make_local_copy (GFile *file, GInputStream *stream)
{
	GsfOutput *out;
	GsfInput  *copy;
	GFileInfo *info;

	out = gsf_output_memory_new ();

	while (1) {
		guint8 buf[4096];
		gssize nread;

		nread = g_input_stream_read (stream, buf, sizeof(buf), NULL, NULL);

		if (nread > 0) {
			if (!gsf_output_write (out, nread, buf)) {
				copy = NULL;
				goto cleanup_and_exit;
			}
		}
		else if (nread == 0)
			break;
		else {
			copy = NULL;
			goto cleanup_and_exit;
		}
	}

	copy = gsf_input_memory_new_clone
		(gsf_output_memory_get_bytes (GSF_OUTPUT_MEMORY (out)),
		 gsf_output_size (out));

	if (copy != NULL) {
		info = g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_NAME, 0, NULL, NULL);
		if (info) {
			gsf_input_set_name (GSF_INPUT (copy), g_file_info_get_name (info));
			g_object_unref (info);
		}
	}

 cleanup_and_exit:

	gsf_output_close (out);
	g_object_unref (out);

	g_input_stream_close (stream, NULL, NULL);
	g_object_unref (stream);

	set_name_from_file (copy, file);

	return copy;
}
