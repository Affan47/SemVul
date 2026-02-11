be_filter_disable(struct bufferevent *bev, short event)
{
	struct bufferevent_filtered *bevf = upcast(bev);
	if (event & EV_WRITE)
		BEV_DEL_GENERIC_WRITE_TIMEOUT(bev);
	if (event & EV_READ) {
		BEV_DEL_GENERIC_READ_TIMEOUT(bev);
		bufferevent_suspend_read(bevf->underlying,
		    BEV_SUSPEND_FILT_READ);
	}
	return 0;
}
