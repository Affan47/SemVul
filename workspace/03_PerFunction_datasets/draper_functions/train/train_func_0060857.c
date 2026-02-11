be_socket_adj_timeouts(struct bufferevent *bufev)
{
	int r = 0;
	if (event_pending(&bufev->ev_read, EV_READ, NULL)) {
		if (evutil_timerisset(&bufev->timeout_read)) {
			    if (be_socket_add(&bufev->ev_read, &bufev->timeout_read) < 0)
				    r = -1;
		} else {
			event_remove_timer(&bufev->ev_read);
		}
	}
	if (event_pending(&bufev->ev_write, EV_WRITE, NULL)) {
		if (evutil_timerisset(&bufev->timeout_write)) {
			if (be_socket_add(&bufev->ev_write, &bufev->timeout_write) < 0)
				r = -1;
		} else {
			event_remove_timer(&bufev->ev_write);
		}
	}
	return r;
}
