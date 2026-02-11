evmap_io_active(struct event_base *base, evutil_socket_t fd, short events)
{
	struct event_io_map *io = &base->io;
	struct evmap_io *ctx;
	struct event *ev;

#ifndef EVMAP_USE_HT
	EVUTIL_ASSERT(fd < io->nentries);
#endif
	GET_IO_SLOT(ctx, io, fd, evmap_io);

	EVUTIL_ASSERT(ctx);
	TAILQ_FOREACH(ev, &ctx->events, ev_io_next) {
		if (ev->ev_events & events)
			event_active_nolock(ev, ev->ev_events & events, 1);
	}
}
