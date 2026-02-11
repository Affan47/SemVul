soup_message_headers_clean_connection_headers (SoupMessageHeaders *hdrs)
{

	const char *connection;
	GSList *tokens, *t;

	connection = soup_message_headers_get_list (hdrs, "Connection");
	if (!connection)
		return;

	tokens = soup_header_parse_list (connection);
	for (t = tokens; t; t = t->next)
		soup_message_headers_remove (hdrs, t->data);
	soup_header_free_list (tokens);
}
