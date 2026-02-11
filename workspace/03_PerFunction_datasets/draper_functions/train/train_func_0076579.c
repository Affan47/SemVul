sashimi_on_connect (GObject* object, GAsyncResult* result, gpointer data)
{
	GSocketClient* client = G_SOCKET_CLIENT(object);
	sashimiConnection* conn = data;
	GTimeVal timeval;
	GError* error = NULL;

	g_mutex_lock(conn->mutex);

	if ((conn->connection = g_socket_client_connect_to_host_finish(client, result, &error)) == NULL)
	{
		if (error != NULL)
		{
			gboolean canceled;

			canceled = (error->domain == G_IO_ERROR && error->code == G_IO_ERROR_CANCELLED);

			g_printerr("CONNECT_ERROR: %s\n", error->message);
			g_error_free(error);

			if (canceled)
			{
				g_mutex_unlock(conn->mutex);
				return;
			}
		}

		goto disconnect;
	}

	conn->stream.input = g_data_input_stream_new(g_io_stream_get_input_stream(G_IO_STREAM(conn->connection)));
	conn->stream.output = g_data_output_stream_new(g_io_stream_get_output_stream(G_IO_STREAM(conn->connection)));

	g_get_current_time(&timeval);
	conn->last_activity = timeval.tv_sec;

	g_data_input_stream_read_line_async(conn->stream.input, G_PRIORITY_DEFAULT, conn->cancellables[c_read], sashimi_on_read, conn);

	conn->sources[s_ping] = sashimi_timeout_add_seconds(conn, 1, sashimi_ping);
	conn->sources[s_queue] = sashimi_timeout_add_seconds(conn, 1, sashimi_queue_runner);

	g_mutex_unlock(conn->mutex);


	if (conn->connect.callback)
	{
		conn->connect.callback(conn->connect.data);
	}

	return;

disconnect:
	g_mutex_unlock(conn->mutex);

	sashimi_disconnect(conn);


	if (conn->disconnect.callback)
	{
		conn->disconnect.callback(conn->disconnect.data);
	}
}
