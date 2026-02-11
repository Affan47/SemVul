handle_unmap_event(XUnmapEvent *e) {
	Client *c = find_client(e->window);

	LOG_ENTER("handle_unmap_event(window=%lx)", e->window);
	if (c) {
		if (c->ignore_unmap) {
			c->ignore_unmap--;
			LOG_DEBUG("ignored (%d ignores remaining)\n", c->ignore_unmap);
		} else {
			LOG_DEBUG("flagging client for removal\n");
			c->remove = 1;
			need_client_tidy = 1;
		}
	} else {
		LOG_DEBUG("unknown client!\n");
	}
	LOG_LEAVE();
}
