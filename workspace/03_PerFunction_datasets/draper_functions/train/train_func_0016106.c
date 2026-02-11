conn_readcb(struct bufferevent *bev, void *arg)
{
	struct conninfo *info = arg;
	struct evbuffer *inbuf = bufferevent_get_input(bev);
	unsigned char *data;
	unsigned char code;


	if (evbuffer_get_length(inbuf) < 8) {
		log_debug("conn: waiting for full socks response");
		return;
	}

	data = evbuffer_pullup(inbuf, 8);
	code = data[1];
	evbuffer_drain(inbuf, 8);

	if (code != 0x5a) {
		finish_connection(info, 0, socks4_error_to_string(code));
	} else {
		finish_connection(info, 1, NULL);
	}
}
