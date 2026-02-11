evthread_make_base_notifiable_nolock_(struct event_base *base)
{
	void (*cb)(evutil_socket_t, short, void *);
	int (*notify)(struct event_base *);

	if (base->th_notify_fn != NULL) {

		return 0;
	}

#if defined(EVENT__HAVE_WORKING_KQUEUE)
	if (base->evsel == &kqops && event_kq_add_notify_event_(base) == 0) {
		base->th_notify_fn = event_kq_notify_base_;


		return 0;
	}
#endif

#ifdef EVENT__HAVE_EVENTFD
	base->th_notify_fd[0] = evutil_eventfd_(0,
	    EVUTIL_EFD_CLOEXEC|EVUTIL_EFD_NONBLOCK);
	if (base->th_notify_fd[0] >= 0) {
		base->th_notify_fd[1] = -1;
		notify = evthread_notify_base_eventfd;
		cb = evthread_notify_drain_eventfd;
	} else
#endif
	if (evutil_make_internal_pipe_(base->th_notify_fd) == 0) {
		notify = evthread_notify_base_default;
		cb = evthread_notify_drain_default;
	} else {
		return -1;
	}

	base->th_notify_fn = notify;


	event_assign(&base->th_notify, base, base->th_notify_fd[0],
				 EV_READ|EV_PERSIST, cb, base);


	base->th_notify.ev_flags |= EVLIST_INTERNAL;
	event_priority_set(&base->th_notify, 0);

	return event_add_nolock_(&base->th_notify, NULL, 0);
}
