evhttp_read_header(struct evhttp_connection *evcon,
		   struct evhttp_request *req)
{
	enum message_read_status res;
	evutil_socket_t fd = evcon->fd;

	res = evhttp_parse_headers_(req, bufferevent_get_input(evcon->bufev));
	if (res == DATA_CORRUPTED || res == DATA_TOO_LONG) {

		event_debug(("%s: bad header lines on "EV_SOCK_FMT"\n",
			__func__, EV_SOCK_ARG(fd)));
		evhttp_connection_fail_(evcon, EVREQ_HTTP_INVALID_HEADER);
		return;
	} else if (res == MORE_DATA_EXPECTED) {

		return;
	}


	bufferevent_disable(evcon->bufev, EV_READ);


	switch (req->kind) {
	case EVHTTP_REQUEST:
		event_debug(("%s: checking for post data on "EV_SOCK_FMT"\n",
			__func__, EV_SOCK_ARG(fd)));
		evhttp_get_body(evcon, req);

		break;

	case EVHTTP_RESPONSE:

		if (req->response_code == 100) {
			evhttp_start_read_(evcon);
			return;
		}
		if (!evhttp_response_needs_body(req)) {
			event_debug(("%s: skipping body for code %d\n",
					__func__, req->response_code));
			evhttp_connection_done(evcon);
		} else {
			event_debug(("%s: start of read body for %s on "
				EV_SOCK_FMT"\n",
				__func__, req->remote_host, EV_SOCK_ARG(fd)));
			evhttp_get_body(evcon, req);


		}
		break;

	default:
		event_warnx("%s: bad header on "EV_SOCK_FMT, __func__,
		    EV_SOCK_ARG(fd));
		evhttp_connection_fail_(evcon, EVREQ_HTTP_INVALID_HEADER);
		break;
	}

}
