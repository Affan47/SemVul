hdhomerun_sock_wait_for_event(hdhomerun_sock_t sock, short event_type, uint64_t stop_time)
{
	uint64_t current_time = getcurrenttime();
	if (current_time >= stop_time) {
		return FALSE;
	}

	struct pollfd poll_event;
	poll_event.fd = sock;
	poll_event.events = event_type;
	poll_event.revents = 0;

	uint64_t timeout = stop_time - current_time;

	if (poll(&poll_event, 1, (int)timeout) <= 0) {
		return FALSE;
	}

	if ((poll_event.revents & event_type) == 0) {
		return FALSE;
	}

	return TRUE;
}
