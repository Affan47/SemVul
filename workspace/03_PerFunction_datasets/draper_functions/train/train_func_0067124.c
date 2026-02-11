event_persist_closure(struct event_base *base, struct event *ev)
{


	void (*evcb_callback)(evutil_socket_t, short, void *);


	if (ev->ev_io_timeout.tv_sec || ev->ev_io_timeout.tv_usec) {


		struct timeval run_at, relative_to, delay, now;
		ev_uint32_t usec_mask = 0;
		EVUTIL_ASSERT(is_same_common_timeout(&ev->ev_timeout,
			&ev->ev_io_timeout));
		gettime(base, &now);
		if (is_common_timeout(&ev->ev_timeout, base)) {
			delay = ev->ev_io_timeout;
			usec_mask = delay.tv_usec & ~MICROSECONDS_MASK;
			delay.tv_usec &= MICROSECONDS_MASK;
			if (ev->ev_res & EV_TIMEOUT) {
				relative_to = ev->ev_timeout;
				relative_to.tv_usec &= MICROSECONDS_MASK;
			} else {
				relative_to = now;
			}
		} else {
			delay = ev->ev_io_timeout;
			if (ev->ev_res & EV_TIMEOUT) {
				relative_to = ev->ev_timeout;
			} else {
				relative_to = now;
			}
		}
		evutil_timeradd(&relative_to, &delay, &run_at);
		if (evutil_timercmp(&run_at, &now, <)) {


			evutil_timeradd(&now, &delay, &run_at);
		}
		run_at.tv_usec |= usec_mask;
		event_add_nolock_(ev, &run_at, 1);
	}


	evcb_callback = *ev->ev_callback;


 	EVBASE_RELEASE_LOCK(base, th_base_lock);


	(evcb_callback)(ev->ev_fd, ev->ev_res, ev->ev_arg);
}
