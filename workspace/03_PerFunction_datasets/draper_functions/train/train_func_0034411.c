process_inbuf(struct http_conn *conn)
{
	struct evbuffer *inbuf = bufferevent_get_input(conn->bev);
	enum http_state state_before;

	if (evbuffer_get_length(inbuf) == 0)
		return;

	do {
		state_before = conn->state;
		process_one_step(conn);
	} while (!conn->read_paused &&
		 evbuffer_get_length(inbuf) > 0 &&
		 state_before != conn->state);
}
