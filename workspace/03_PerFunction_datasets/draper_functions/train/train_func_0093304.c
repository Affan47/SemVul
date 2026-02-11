schedule(struct proxydesc *d)
{
	short ev = 0;


	if (PENDINGDATA(d))
		ev |= EV_WRITE;


	if (d->dst->pos < d->dst->iov.iov_len &&
	    !(ISSET(d->state, NET_STATE_EOFPENDING) && PENDINGDATA(d->dst)))
		ev |= EV_READ;

	if (ev == 0)
		return;

	event_set(d->ev, d->sock, ev, proxy, d);
	if (event_add(d->ev, NULL) == -1) {
		cleanup_cleanup(cleanup);
		errv(0, 1, "event_add()");
	}
}
