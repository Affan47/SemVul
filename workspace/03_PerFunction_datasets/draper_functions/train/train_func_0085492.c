evmap_check_integrity(struct event_base *base)
{
#define EVLIST_X_SIGFOUND 0x1000
#define EVLIST_X_IOFOUND 0x2000

	evutil_socket_t i;
	struct event *ev;
	struct event_io_map *io = &base->io;
	struct event_signal_map *sigmap = &base->sigmap;
#ifdef EVMAP_USE_HT
	struct event_map_entry **mapent;
#endif
	int nsignals, ntimers, nio;
	nsignals = ntimers = nio = 0;

	TAILQ_FOREACH(ev, &base->eventqueue, ev_next) {
		EVUTIL_ASSERT(ev->ev_flags & EVLIST_INSERTED);
		EVUTIL_ASSERT(ev->ev_flags & EVLIST_INIT);
		ev->ev_flags &= ~(EVLIST_X_SIGFOUND|EVLIST_X_IOFOUND);
	}

#ifdef EVMAP_USE_HT
	HT_FOREACH(mapent, event_io_map, io) {
		struct evmap_io *ctx = &(*mapent)->ent.evmap_io;
		i = (*mapent)->fd;
#else
	for (i = 0; i < io->nentries; ++i) {
		struct evmap_io *ctx = io->entries[i];

		if (!ctx)
			continue;
#endif

		TAILQ_FOREACH(ev, &ctx->events, ev_io_next) {
			EVUTIL_ASSERT(!(ev->ev_flags & EVLIST_X_IOFOUND));
			EVUTIL_ASSERT(ev->ev_fd == i);
			ev->ev_flags |= EVLIST_X_IOFOUND;
			nio++;
		}
	}

	for (i = 0; i < sigmap->nentries; ++i) {
		struct evmap_signal *ctx = sigmap->entries[i];
		if (!ctx)
			continue;

		TAILQ_FOREACH(ev, &ctx->events, ev_signal_next) {
			EVUTIL_ASSERT(!(ev->ev_flags & EVLIST_X_SIGFOUND));
			EVUTIL_ASSERT(ev->ev_fd == i);
			ev->ev_flags |= EVLIST_X_SIGFOUND;
			nsignals++;
		}
	}

	TAILQ_FOREACH(ev, &base->eventqueue, ev_next) {
		if (ev->ev_events & (EV_READ|EV_WRITE)) {
			EVUTIL_ASSERT(ev->ev_flags & EVLIST_X_IOFOUND);
			--nio;
		}
		if (ev->ev_events & EV_SIGNAL) {
			EVUTIL_ASSERT(ev->ev_flags & EVLIST_X_SIGFOUND);
			--nsignals;
		}
	}

	EVUTIL_ASSERT(nio == 0);
	EVUTIL_ASSERT(nsignals == 0);


}
