tgt_event_add(int fd, int events, event_handler_t handler, void *data)
{
	struct epoll_event ev;
	struct event_data *tev;
	int err;

	tev = zalloc(sizeof(*tev));
	if (!tev)
		return -ENOMEM;

	tev->data = data;
	tev->handler = handler;
	tev->fd = fd;

	memset(&ev, 0, sizeof(ev));
	ev.events = events;
	ev.data.ptr = tev;
	err = epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd, &ev);
	if (err) {
		eprintf("Cannot add fd, %m\n");
		free(tev);
	} else
		list_add(&tev->e_list, &tgt_events_list);

	return err;
}
