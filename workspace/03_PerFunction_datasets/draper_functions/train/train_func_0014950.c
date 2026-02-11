event_queue_remove(struct event_base *base, struct event *ev, int queue)
{
	EVENT_BASE_ASSERT_LOCKED(base);

	if (!(ev->ev_flags & queue)) {
		event_errx(1, "%s: %p(fd "EV_SOCK_FMT") not on queue %x", __func__,
		    ev, EV_SOCK_ARG(ev->ev_fd), queue);
		return;
	}

	if (~ev->ev_flags & EVLIST_INTERNAL)
		base->event_count--;

	ev->ev_flags &= ~queue;
	switch (queue) {
	case EVLIST_INSERTED:
		TAILQ_REMOVE(&base->eventqueue, ev, ev_next);
		break;
	case EVLIST_ACTIVE:
		base->event_count_active--;
		TAILQ_REMOVE(&base->activequeues[ev->ev_pri],
		    ev, ev_active_next);
		break;
	case EVLIST_TIMEOUT:
		if (is_common_timeout(&ev->ev_timeout, base)) {
			struct common_timeout_list *ctl =
			    get_common_timeout_list(base, &ev->ev_timeout);
			TAILQ_REMOVE(&ctl->events, ev,
			    ev_timeout_pos.ev_next_with_common_timeout);
		} else {
			min_heap_erase(&base->timeheap, ev);
		}
		break;
	default:
		event_errx(1, "%s: unknown queue %x", __func__, queue);
	}
}
