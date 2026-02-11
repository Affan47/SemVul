send_chunked_file (SoupServer * server, SoupMessage * message,
		   DPAPRecord * record, guint64 filesize)
{
	GInputStream *stream;
	const char *location;
	GError *error = NULL;
	ChunkData *cd = g_new (ChunkData, 1);

	g_object_get (record, "location", &location, NULL);

	cd->server = server;

	stream = G_INPUT_STREAM (dpap_record_read (record, &error));

	if (error != NULL) {
		g_warning ("Couldn't open %s: %s.", location, error->message);
		g_error_free (error);
		soup_message_set_status (message,
					 SOUP_STATUS_INTERNAL_SERVER_ERROR);
		g_free (cd);
		return;
	}

	cd->stream = stream;

	if (cd->stream == NULL) {
		g_warning ("Could not set up input stream");
		g_free (cd);
		return;
	}

	soup_message_headers_set_encoding (message->response_headers,
					   SOUP_ENCODING_CONTENT_LENGTH);
	soup_message_headers_set_content_length (message->response_headers,
						 filesize);

	soup_message_headers_append (message->response_headers, "Connection",
				     "Close");
	soup_message_headers_append (message->response_headers,
				     "Content-Type",
				     "application/x-dmap-tagged");

	g_signal_connect (message, "wrote_headers",
			  G_CALLBACK (dmap_write_next_chunk), cd);
	g_signal_connect (message, "wrote_chunk",
			  G_CALLBACK (dmap_write_next_chunk), cd);
	g_signal_connect (message, "finished",
			  G_CALLBACK (dmap_chunked_message_finished), cd);

}
