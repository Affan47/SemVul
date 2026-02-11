start_writing(struct bufferevent_openssl *bev_ssl)
{
	int r;
	if (bev_ssl->underlying) {
		short e = EV_WRITE;
		if (bev_ssl->write_blocked_on_read)
			e |= EV_READ;
		r = bufferevent_enable(bev_ssl->underlying, e);
	} else {
		struct bufferevent *bev = &bev_ssl->bev.bev;
		r = _bufferevent_add_event(&bev->ev_write, &bev->timeout_write);
		if (!r && bev_ssl->write_blocked_on_read)
			r = _bufferevent_add_event(&bev->ev_read,
			    &bev->timeout_read);
	}
	return r;
}
