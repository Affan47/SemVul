server_callback (SoupServer *server, SoupMessage *msg,
		 const char *path, GHashTable *query,
		 SoupClientContext *context, gpointer data)
{
	if (msg->method != SOUP_METHOD_GET && msg->method != SOUP_METHOD_HEAD) {
		soup_message_set_status (msg, SOUP_STATUS_NOT_IMPLEMENTED);
		return;
	}

	soup_message_set_response (msg, "text/plain",
				   SOUP_MEMORY_STATIC,
				   "OK\r\n", 4);
	soup_message_set_status (msg, SOUP_STATUS_OK);
}
