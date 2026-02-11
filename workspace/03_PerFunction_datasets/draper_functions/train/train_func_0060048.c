levent_ctl_recv(struct bufferevent *bev, void *ptr)
{
	struct lldpd_one_client *client = ptr;
	struct evbuffer *buffer = bufferevent_get_input(bev);
	size_t buffer_len       = evbuffer_get_length(buffer);
	struct hmsg_header hdr;
	void *data = NULL;

	log_debug("control", "receive data on Unix socket");
	if (buffer_len < sizeof(struct hmsg_header))
		return;
	if (evbuffer_copyout(buffer, &hdr,
		sizeof(struct hmsg_header)) != sizeof(struct hmsg_header)) {
		log_warnx("event", "not able to read header");
		return;
	}
	if (hdr.len > HMSG_MAX_SIZE) {
		log_warnx("event", "message received is too large");
		goto recv_error;
	}

	if (buffer_len < hdr.len + sizeof(struct hmsg_header))
		return;
	if (hdr.len > 0 && (data = malloc(hdr.len)) == NULL) {
		log_warnx("event", "not enough memory");
		goto recv_error;
	}
	evbuffer_drain(buffer, sizeof(struct hmsg_header));
	if (hdr.len > 0) evbuffer_remove(buffer, data, hdr.len);


	if (hdr.len == 0 && hdr.type == NOTIFICATION) return;
	if (client_handle_client(client->cfg,
		levent_ctl_send_cb, client,
		hdr.type, data, hdr.len,
		&client->subscribed) == -1) goto recv_error;
	free(data);
	return;

recv_error:
	free(data);
	levent_ctl_free_client(client);
}
