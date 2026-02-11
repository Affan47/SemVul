bufferevent_run_readcb_(struct bufferevent *bufev, int options)
{

	struct bufferevent_private *p =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	if (bufev->readcb == NULL)
		return;
	if ((p->options|options) & BEV_OPT_DEFER_CALLBACKS) {
		p->readcb_pending = 1;
		SCHEDULE_DEFERRED(p);
	} else {
		bufev->readcb(bufev, bufev->cbarg);
	}
}
