evhttp_write_cb(struct bufferevent *bufev, void *arg)
{
	struct evhttp_connection *evcon = arg;


	if (evcon->cb != NULL)
		(*evcon->cb)(evcon, evcon->cb_arg);
}
