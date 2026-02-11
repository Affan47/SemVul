daap_request_stream (GIOChannel *chan, gchar *path, gchar *host,
                     guint request_id, guint *size)
{
	guint status;
	gchar *request, *header = NULL;

	request = daap_generate_request (path, host, request_id);
	daap_send_request (chan, request);
	g_free (request);

	daap_receive_header (chan, &header);
	if (!header) {
		return FALSE;
	}

	status = get_server_status (header);
	if (HTTP_OK != status) {
		g_free (header);
		return FALSE;
	}

	*size = get_data_length (header);

	g_free (header);

	return TRUE;
}
