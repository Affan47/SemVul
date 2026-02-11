soup_message_send_request (SoupMessageQueueItem      *item,
			   SoupMessageCompletionFn    completion_cb,
			   gpointer                   user_data)
{
	GMainContext *async_context;
	GIOStream *iostream;

	if (!SOUP_IS_SESSION_SYNC (item->session)) {
		async_context = soup_session_get_async_context (item->session);
		if (!async_context)
			async_context = g_main_context_default ();
	} else
		async_context = NULL;
	iostream = soup_socket_get_iostream (soup_connection_get_socket (item->conn));

	soup_message_io_client (item, iostream, async_context,
				get_request_headers,
				parse_response_headers,
				item,
				completion_cb, user_data);
}
