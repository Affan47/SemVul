evhttp_connection_base_bufferevent_new(struct event_base *base, struct evdns_base *dnsbase, struct bufferevent* bev,
    const char *address, unsigned short port)
{
	struct evhttp_connection *evcon = NULL;

	event_debug(("Attempting connection to %s:%d\n", address, port));

	if ((evcon = mm_calloc(1, sizeof(struct evhttp_connection))) == NULL) {
		event_warn("%s: calloc failed", __func__);
		goto error;
	}

	evcon->fd = -1;
	evcon->port = port;

	evcon->max_headers_size = EV_SIZE_MAX;
	evcon->max_body_size = EV_SIZE_MAX;

	evutil_timerclear(&evcon->timeout);
	evcon->retry_cnt = evcon->retry_max = 0;

	if ((evcon->address = mm_strdup(address)) == NULL) {
		event_warn("%s: strdup failed", __func__);
		goto error;
	}

	if (bev == NULL) {
		if (!(bev = bufferevent_socket_new(base, -1, 0))) {
			event_warn("%s: bufferevent_socket_new failed", __func__);
			goto error;
		}
	}

	bufferevent_setcb(bev, evhttp_read_cb, evhttp_write_cb, evhttp_error_cb, evcon);
	evcon->bufev = bev;

	evcon->state = EVCON_DISCONNECTED;
	TAILQ_INIT(&evcon->requests);

	evcon->initial_retry_timeout.tv_sec = 2;
	evcon->initial_retry_timeout.tv_usec = 0;

	if (base != NULL) {
		evcon->base = base;
		if (bufferevent_get_base(bev) != base)
			bufferevent_base_set(base, evcon->bufev);
	}

	event_deferred_cb_init_(
	    &evcon->read_more_deferred_cb,
	    bufferevent_get_priority(bev),
	    evhttp_deferred_read_cb, evcon);

	evcon->dns_base = dnsbase;

	return (evcon);

 error:
	if (evcon != NULL)
		evhttp_connection_free(evcon);
	return (NULL);
}
