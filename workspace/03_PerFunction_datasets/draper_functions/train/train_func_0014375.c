evhttp_accept_socket_with_handle(struct evhttp *http, evutil_socket_t fd)
{
	struct evhttp_bound_socket *bound;
	struct evconnlistener *listener;
	const int flags =
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_EXEC|LEV_OPT_CLOSE_ON_FREE;

	listener = evconnlistener_new(http->base, NULL, NULL,
	    flags,
	    0,
	    fd);
	if (!listener)
		return (NULL);

	bound = evhttp_bind_listener(http, listener);
	if (!bound) {
		evconnlistener_free(listener);
		return (NULL);
	}
	return (bound);
}
