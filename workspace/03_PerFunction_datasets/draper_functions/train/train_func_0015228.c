search_file_command_load (SearchFileCommand* cmd, GError **error)
{
	GString* content;
	GFileInputStream* istream;
	gchar buffer[BUFFER_SIZE];
	gssize bytes_read;

	istream = g_file_read (cmd->priv->file, NULL, error);
	if (*error)
	{
		return NULL;
	}


	content = g_string_new (NULL);
	while ((bytes_read = g_input_stream_read (G_INPUT_STREAM (istream),
	                                          buffer,
	                                          BUFFER_SIZE - 1,
	                                          NULL,
	                                          error)))
	{
		if (*error)
		{
			g_string_free (content, TRUE);
			g_object_unref (istream);
			return NULL;
		}

		g_string_append_len (content, buffer, bytes_read);
	}
	g_object_unref (istream);

	return g_string_free (content, FALSE);
}
