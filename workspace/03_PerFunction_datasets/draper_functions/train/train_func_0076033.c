evhttp_get_request(struct evhttp *http, evutil_socket_t fd,
    struct sockaddr *sa, ev_socklen_t salen)
{
	struct evhttp_connection *evcon;

	evcon = evhttp_get_request_connection(http, fd, sa, salen);
	if (evcon == NULL) {
		event_sock_warn(fd, "%s: cannot get connection on %d", __func__, fd);
		EVUTIL_CLOSESOCKET(fd);
		return;
	}


	if (http->timeout != -1)
		evhttp_connection_set_timeout(evcon, http->timeout);


	evcon->http_server = http;
	TAILQ_INSERT_TAIL(&http->connections, evcon, next);

	if (evhttp_associate_new_request_with_connection(evcon) == -1)
		evhttp_connection_free(evcon);
}
