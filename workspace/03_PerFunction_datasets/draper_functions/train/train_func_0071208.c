tunnel_transfer_data(struct http_conn *conn, struct bufferevent *to,
		     struct bufferevent *from)
{
	struct evbuffer *frombuf = bufferevent_get_input(from);
	struct evbuffer *tobuf = bufferevent_get_output(to);

	if (evbuffer_get_length(frombuf) == 0)
		return;

	evbuffer_add_buffer(tobuf, frombuf);
	if (evbuffer_get_length(tobuf) > max_write_backlog) {
		bufferevent_setwatermark(to, EV_WRITE,
					 max_write_backlog / 2, 0);
		bufferevent_disable(from, EV_READ);
		if (from == conn->bev) {
			log_debug("tunnel: throttling client read");
			conn->read_paused = 1;
		} else {
			log_debug("tunnel: throttling server read");
			conn->tunnel_read_paused = 1;
		}
	}
}
