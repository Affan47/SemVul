done_writing_cb(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *b = bufferevent_get_output(bev);
	if (evbuffer_get_length(b))
		return;
	TT_BLATHER(("Done writing."));
	bufferevent_disable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
}
