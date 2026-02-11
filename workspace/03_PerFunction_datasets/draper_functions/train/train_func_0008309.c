bufferevent_enable(struct bufferevent *bufev, short event)
{
	struct bufferevent_private *bufev_private =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	short impl_events = event;
	int r = 0;

	_bufferevent_incref_and_lock(bufev);
	if (bufev_private->read_suspended)
		impl_events &= ~EV_READ;
	if (bufev_private->write_suspended)
		impl_events &= ~EV_WRITE;

	bufev->enabled |= event;

	if (impl_events && bufev->be_ops->enable(bufev, impl_events) < 0)
		r = -1;

	_bufferevent_decref_and_unlock(bufev);
	return r;
}
