start_request (SoupServer *server, SoupClientContext *client)
{
	SoupServerPrivate *priv = SOUP_SERVER_GET_PRIVATE (server);
	SoupMessage *msg;

	soup_client_context_cleanup (client);


	msg = g_object_new (SOUP_TYPE_MESSAGE,
			    SOUP_MESSAGE_SERVER_SIDE, TRUE,
			    NULL);
	client->msg = msg;

	if (priv->server_header) {
		soup_message_headers_append (msg->response_headers, "Server",
					     priv->server_header);
	}

	g_signal_connect (msg, "got_headers", G_CALLBACK (got_headers), client);
	g_signal_connect (msg, "got_body", G_CALLBACK (call_handler), client);

	g_signal_emit (server, signals[REQUEST_STARTED], 0,
		       msg, client);

	g_object_ref (client->sock);

	if (priv->async_context)
		g_main_context_push_thread_default (priv->async_context);
	soup_message_read_request (msg, client->sock,
				   request_finished, client);
	if (priv->async_context)
		g_main_context_pop_thread_default (priv->async_context);
}
