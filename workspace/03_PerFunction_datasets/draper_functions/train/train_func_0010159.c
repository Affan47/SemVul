be_pair_flush(struct bufferevent *bev, short iotype,
    enum bufferevent_flush_mode mode)
{
	struct bufferevent_pair *bev_p = upcast(bev);
	struct bufferevent *partner;
	incref_and_lock(bev);
	if (!bev_p->partner)
		return -1;

	partner = downcast(bev_p->partner);

	if (mode == BEV_NORMAL)
		return 0;

	if ((iotype & EV_READ) != 0)
		be_pair_transfer(partner, bev, 1);

	if ((iotype & EV_WRITE) != 0)
		be_pair_transfer(bev, partner, 1);

	if (mode == BEV_FINISHED) {
		bufferevent_run_eventcb_(partner, iotype|BEV_EVENT_EOF);
	}
	decref_and_unlock(bev);
	return 0;
}
