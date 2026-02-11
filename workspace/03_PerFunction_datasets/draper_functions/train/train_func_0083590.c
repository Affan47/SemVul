evhttp_free(struct evhttp* http)
{
	struct evhttp_cb *http_cb;
	struct evhttp_connection *evcon;
	struct evhttp_bound_socket *bound;
	struct evhttp* vhost;
	struct evhttp_server_alias *alias;


	while ((bound = TAILQ_FIRST(&http->sockets)) != NULL) {
		TAILQ_REMOVE(&http->sockets, bound, next);

		evconnlistener_free(bound->listener);

		mm_free(bound);
	}

	while ((evcon = TAILQ_FIRST(&http->connections)) != NULL) {

		evhttp_connection_free(evcon);
	}

	while ((http_cb = TAILQ_FIRST(&http->callbacks)) != NULL) {
		TAILQ_REMOVE(&http->callbacks, http_cb, next);
		mm_free(http_cb->what);
		mm_free(http_cb);
	}

	while ((vhost = TAILQ_FIRST(&http->virtualhosts)) != NULL) {
		TAILQ_REMOVE(&http->virtualhosts, vhost, next_vhost);

		evhttp_free(vhost);
	}

	if (http->vhost_pattern != NULL)
		mm_free(http->vhost_pattern);

	while ((alias = TAILQ_FIRST(&http->aliases)) != NULL) {
		TAILQ_REMOVE(&http->aliases, alias, next);
		mm_free(alias->alias);
		mm_free(alias);
	}

	mm_free(http);
}
