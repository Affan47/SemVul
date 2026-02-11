readcb(struct bufferevent *bev, void *arg)
{
	struct node *node = arg;
	const char *buf;
	const char *end;
	int drain_all = 0;

	for (;;) {
		buf = (const char *)EVBUFFER_DATA(bev->input);
		end = (const char *)evbuffer_find(bev->input,
				(u_char *)"\r\n", 2);
		if (!end)
			return;

		if (!drain_all)
			drain_all = proc_msg(buf, end - buf, node);
		evbuffer_drain(bev->input, end - buf + 2);
	}
}
