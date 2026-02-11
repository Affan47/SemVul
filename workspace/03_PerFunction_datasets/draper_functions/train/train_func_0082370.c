poll_dispatch(struct event_base *base, struct timeval *tv)
{
	int res, i, j, nfds;
	long msec = -1;
	struct pollop *pop = base->evbase;
	struct pollfd *event_set;

	poll_check_ok(pop);

	nfds = pop->nfds;

#ifndef _EVENT_DISABLE_THREAD_SUPPORT
	if (base->th_base_lock) {


		if (pop->realloc_copy) {
			struct pollfd *tmp = mm_realloc(pop->event_set_copy,
			    pop->event_count * sizeof(struct pollfd));
			if (tmp == NULL) {
				event_warn("realloc");
				return -1;
			}
			pop->event_set_copy = tmp;
			pop->realloc_copy = 0;
		}
		memcpy(pop->event_set_copy, pop->event_set,
		    sizeof(struct pollfd)*nfds);
		event_set = pop->event_set_copy;
	} else {
		event_set = pop->event_set;
	}
#else
	event_set = pop->event_set;
#endif

	if (tv != NULL) {
		msec = evutil_tv_to_msec(tv);
		if (msec < 0 || msec > INT_MAX)
			msec = INT_MAX;
	}

	EVBASE_RELEASE_LOCK(base, th_base_lock);

	res = poll(event_set, nfds, msec);

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);

	if (res == -1) {
		if (errno != EINTR) {
			event_warn("poll");
			return (-1);
		}

		return (0);
	}

	event_debug(("%s: poll reports %d", __func__, res));

	if (res == 0 || nfds == 0)
		return (0);

	i = random() % nfds;
	for (j = 0; j < nfds; j++) {
		int what;
		if (++i == nfds)
			i = 0;
		what = event_set[i].revents;
		if (!what)
			continue;

		res = 0;


		if (what & (POLLHUP|POLLERR))
			what |= POLLIN|POLLOUT;
		if (what & POLLIN)
			res |= EV_READ;
		if (what & POLLOUT)
			res |= EV_WRITE;
		if (res == 0)
			continue;

		evmap_io_active(base, event_set[i].fd, res);
	}

	return (0);
}
