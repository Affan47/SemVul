send_data(GIOChannel *channel, GIOCondition cond,
						gpointer user_data)
{
	struct web_session *session = user_data;

	if (cond & (G_IO_NVAL | G_IO_ERR | G_IO_HUP)) {
		session->send_watch = 0;
		return FALSE;
	}

	if (process_send_buffer(session) == TRUE)
		return TRUE;

	if (process_send_file(session) == TRUE)
		return TRUE;

	if (session->request_started == FALSE) {
		session->request_started = TRUE;
		start_request(session);
	} else if (session->more_data == TRUE)
		process_next_chunk(session);

	process_send_buffer(session);

	if (session->body_done == TRUE) {
		session->send_watch = 0;
		return FALSE;
	}

	return TRUE;
}
