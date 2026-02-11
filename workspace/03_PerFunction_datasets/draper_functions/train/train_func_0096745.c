do_temporary_test (SoupSession *session, SoupURI *base_uri)
{
	SoupMessage *msg;
	char *client_md5;
	const char *server_md5;

	debug_printf (1, "PUT w/ temporary buffers\n");

	msg = soup_message_new_from_uri ("PUT", base_uri);
	soup_message_body_append (msg->request_body, SOUP_MEMORY_TEMPORARY,
				  "one\r\n", 5);
	soup_message_body_append (msg->request_body, SOUP_MEMORY_STATIC,
				  "two\r\n", 5);
	soup_message_body_set_accumulate (msg->request_body, FALSE);

	client_md5 = g_compute_checksum_for_string (G_CHECKSUM_MD5,
						    "one\r\ntwo\r\n", 10);
	g_signal_connect (msg, "wrote_chunk",
			  G_CALLBACK (temp_test_wrote_chunk), session);
	soup_session_send_message (session, msg);

	if (!SOUP_STATUS_IS_SUCCESSFUL (msg->status_code)) {
		debug_printf (1, "  message failed: %d %s\n",
			      msg->status_code, msg->reason_phrase);
		errors++;
	}

	server_md5 = soup_message_headers_get_one (msg->response_headers,
						   "Content-MD5");
	if (!server_md5 || strcmp (client_md5, server_md5) != 0) {
		debug_printf (1, "  client/server data mismatch: %s vs %s\n",
			      client_md5, server_md5 ? server_md5 : "(null)");
		errors++;
	}

	g_free (client_md5);
	g_object_unref (msg);
}
