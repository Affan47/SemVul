save_contents_vfs (const char *filename, const char *str, int size)
{
	GFile* file;
	GFileOutputStream* stream;
	gsize bytes;

	file = g_file_new_for_uri (filename);
	stream = g_file_replace (file, NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL);

	if (stream == NULL)
	{
		g_object_unref (file);
		return FALSE;
	}

	g_output_stream_write_all (G_OUTPUT_STREAM (stream), str, size, &bytes, NULL, NULL);

	if (bytes != size)
	{
		g_object_unref(stream);
		g_object_unref(file);
		return FALSE;
	}

	if (size > 0 && str[size-1] != '\n')
		g_output_stream_write (G_OUTPUT_STREAM (stream), "\n", 1, NULL, NULL);

	g_output_stream_close (G_OUTPUT_STREAM (stream), NULL, NULL);
	g_object_unref (stream);
	g_object_unref (file);

	return TRUE;
}
