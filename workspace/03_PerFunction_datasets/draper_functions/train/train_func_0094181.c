epoll_dispatch(struct event_base *base, void *arg, struct timeval *tv)
{
	struct epollop *epollop = arg;
	struct epoll_event *events = epollop->events;
	struct evepoll *evep;
	int i, res, timeout = -1;

	if (tv != NULL)
		timeout = tv->tv_sec * 1000 + (tv->tv_usec + 999) / 1000;

	if (timeout > MAX_EPOLL_TIMEOUT_MSEC) {


		timeout = MAX_EPOLL_TIMEOUT_MSEC;
	}

	res = epoll_wait(epollop->epfd, events, epollop->nevents, timeout);

	if (res == -1) {
		if (errno != EINTR) {
			event_warn("epoll_wait");
			return (-1);
		}

		evsignal_process(base);
		return (0);
	} else if (base->sig.evsignal_caught) {
		evsignal_process(base);
	}

	event_debug(("%s: epoll_wait reports %d", __func__, res));

	for (i = 0; i < res; i++) {
		int what = events[i].events;
		struct event *evread = NULL, *evwrite = NULL;
		int fd = events[i].data.fd;

		if (fd < 0 || fd >= epollop->nfds)
			continue;
		evep = &epollop->fds[fd];

		if (what & (EPOLLHUP|EPOLLERR)) {
			evread = evep->evread;
			evwrite = evep->evwrite;
		} else {
			if (what & EPOLLIN) {
				evread = evep->evread;
			}

			if (what & EPOLLOUT) {
				evwrite = evep->evwrite;
			}
		}

		if (!(evread||evwrite))
			continue;

		if (evread != NULL)
			event_active(evread, EV_READ, 1);
		if (evwrite != NULL)
			event_active(evwrite, EV_WRITE, 1);
	}

	if (res == epollop->nevents && epollop->nevents < MAX_NEVENTS) {


		int new_nevents = epollop->nevents * 2;
		struct epoll_event *new_events;

		new_events = realloc(epollop->events,
		    new_nevents * sizeof(struct epoll_event));
		if (new_events) {
			epollop->events = new_events;
			epollop->nevents = new_nevents;
		}
	}

	return (0);
}
