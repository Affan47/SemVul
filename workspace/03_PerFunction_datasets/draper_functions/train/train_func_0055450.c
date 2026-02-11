event_pending(struct event *ev, short event, struct timeval *tv)
{
	struct timeval	now, res;
	int flags = 0;

	_event_debug_assert_is_setup(ev);

	if (ev->ev_flags & EVLIST_INSERTED)
		flags |= (ev->ev_events & (EV_READ|EV_WRITE|EV_SIGNAL));
	if (ev->ev_flags & EVLIST_ACTIVE)
		flags |= ev->ev_res;
	if (ev->ev_flags & EVLIST_TIMEOUT)
		flags |= EV_TIMEOUT;

	event &= (EV_TIMEOUT|EV_READ|EV_WRITE|EV_SIGNAL);


	if (tv != NULL && (flags & event & EV_TIMEOUT)) {
		struct timeval tmp = ev->ev_timeout;
		gettime(ev->ev_base, &now);
		tmp.tv_usec &= MICROSECONDS_MASK;
		evutil_timersub(&tmp, &now, &res);

		evutil_gettimeofday(&now, NULL);
		evutil_timeradd(&now, &res, tv);
	}

	return (flags & event);
}
