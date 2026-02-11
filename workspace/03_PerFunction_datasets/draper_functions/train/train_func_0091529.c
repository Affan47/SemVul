evhttp_connection_base_new(struct event_base *base, struct evdns_base *dnsbase,
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

	evcon->timeout = -1;
	evcon->retry_cnt = evcon->retry_max = 0;

	if ((evcon->address = mm_strdup(address)) == NULL) {
		event_warn("%s: strdup failed", __func__);
		goto error;
	}

	if ((evcon->bufev = bufferevent_new(-1,
		    evhttp_read_cb,
		    evhttp_write_cb,
		    evhttp_error_cb, evcon)) == NULL) {
		event_warn("%s: bufferevent_new failed", __func__);
		goto error;
	}

	evcon->state = EVCON_DISCONNECTED;
	TAILQ_INIT(&evcon->requests);

	if (base != NULL) {
		evcon->base = base;
		bufferevent_base_set(base, evcon->bufev);
	}


	event_deferred_cb_init(&evcon->read_more_deferred_cb,
	    evhttp_deferred_read_cb, evcon);

	evcon->dns_base = dnsbase;

	return (evcon);

 error:
	if (evcon != NULL)
		evhttp_connection_free(evcon);
	return (NULL);
}
