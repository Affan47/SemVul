bufferevent_set_timeouts(struct bufferevent *bufev,
			 const struct timeval *tv_read,
			 const struct timeval *tv_write)
{
	int r = 0;
	BEV_LOCK(bufev);
	if (tv_read) {
		bufev->timeout_read = *tv_read;
	} else {
		evutil_timerclear(&bufev->timeout_read);
	}
	if (tv_write) {
		bufev->timeout_write = *tv_write;
	} else {
		evutil_timerclear(&bufev->timeout_write);
	}

	if (bufev->be_ops->adj_timeouts)
		r = bufev->be_ops->adj_timeouts(bufev);
	BEV_UNLOCK(bufev);

	return r;
}
