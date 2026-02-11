soup_multipart_to_message (SoupMultipart *multipart,
			   SoupMessageHeaders *dest_headers,
			   SoupMessageBody *dest_body)
{
	SoupMessageHeaders *part_headers;
	SoupBuffer *part_body;
	SoupMessageHeadersIter iter;
	const char *name, *value;
	GString *str;
	GHashTable *params;
	int i;

	params = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (params, "boundary", multipart->boundary);
	soup_message_headers_set_content_type (dest_headers,
					       multipart->mime_type,
					       params);
	g_hash_table_destroy (params);

	for (i = 0; i < multipart->bodies->len; i++) {
		part_headers = multipart->headers->pdata[i];
		part_body = multipart->bodies->pdata[i];

		str = g_string_new (i == 0 ? NULL : "\r\n");
		g_string_append (str, "--");
		g_string_append (str, multipart->boundary);
		g_string_append (str, "\r\n");
		soup_message_headers_iter_init (&iter, part_headers);
		while (soup_message_headers_iter_next (&iter, &name, &value))
			g_string_append_printf (str, "%s: %s\r\n", name, value);
		g_string_append (str, "\r\n");
		soup_message_body_append (dest_body, SOUP_MEMORY_TAKE,
					  str->str, str->len);
		g_string_free (str, FALSE);

		soup_message_body_append_buffer (dest_body, part_body);
	}

	str = g_string_new ("\r\n--");
	g_string_append (str, multipart->boundary);
	g_string_append (str, "--\r\n");
	soup_message_body_append (dest_body, SOUP_MEMORY_TAKE,
				  str->str, str->len);
	g_string_free (str, FALSE);


}
