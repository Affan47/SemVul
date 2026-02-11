evhttp_connection_connect_(struct evhttp_connection *evcon)
{
	int old_state = evcon->state;

	if (evcon->state == EVCON_CONNECTING)
		return (0);

	evhttp_connection_reset_(evcon);

	EVUTIL_ASSERT(!(evcon->flags & EVHTTP_CON_INCOMING));
	evcon->flags |= EVHTTP_CON_OUTGOING;

	if (evcon->bind_address || evcon->bind_port) {
		evcon->fd = bind_socket(
			evcon->bind_address, evcon->bind_port, 0 );
		if (evcon->fd == -1) {
			event_debug(("%s: failed to bind to \"%s\"",
				__func__, evcon->bind_address));
			return (-1);
		}

		bufferevent_setfd(evcon->bufev, evcon->fd);
	} else {
		bufferevent_setfd(evcon->bufev, -1);
	}


	bufferevent_setcb(evcon->bufev,
	    NULL ,
	    NULL ,
	    evhttp_connection_cb,
	    evcon);
	if (!evutil_timerisset(&evcon->timeout)) {
		const struct timeval conn_tv = { HTTP_CONNECT_TIMEOUT, 0 };
		bufferevent_set_timeouts(evcon->bufev, NULL, &conn_tv);
	} else {
		bufferevent_set_timeouts(evcon->bufev, NULL, &evcon->timeout);
	}

	bufferevent_enable(evcon->bufev, EV_WRITE);

	evcon->state = EVCON_CONNECTING;

	if (bufferevent_socket_connect_hostname(evcon->bufev, evcon->dns_base,
		AF_UNSPEC, evcon->address, evcon->port) < 0) {
		evcon->state = old_state;
		event_sock_warn(evcon->fd, "%s: connection to \"%s\" failed",
		    __func__, evcon->address);


		evhttp_connection_cb_cleanup(evcon);
		return (0);
	}

	return (0);
}
