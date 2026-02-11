be_pair_disable(struct bufferevent *bev, short events)
{
	if (events & EV_READ) {
		BEV_DEL_GENERIC_READ_TIMEOUT(bev);
	}
	if (events & EV_WRITE) {
		BEV_DEL_GENERIC_WRITE_TIMEOUT(bev);
	}
	return 0;
}
