bufferevent_readcb(evutil_socket_t fd, short event, void *arg)
{
	struct bufferevent *bufev = arg;
	struct bufferevent_private *bufev_p =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	struct evbuffer *input;
	int res = 0;
	short what = BEV_EVENT_READING;
	ev_ssize_t howmuch = -1, readmax=-1;

	bufferevent_incref_and_lock_(bufev);

	if (event == EV_TIMEOUT) {


		what |= BEV_EVENT_TIMEOUT;
		goto error;
	}

	input = bufev->input;


	if (bufev->wm_read.high != 0) {
		howmuch = bufev->wm_read.high - evbuffer_get_length(input);

		if (howmuch <= 0) {
			bufferevent_wm_suspend_read(bufev);
			goto done;
		}
	}
	readmax = bufferevent_get_read_max_(bufev_p);
	if (howmuch < 0 || howmuch > readmax)

		howmuch = readmax;
	if (bufev_p->read_suspended)
		goto done;

	evbuffer_unfreeze(input, 0);
	res = evbuffer_read(input, fd, (int)howmuch);
	evbuffer_freeze(input, 0);

	if (res == -1) {
		int err = evutil_socket_geterror(fd);
		if (EVUTIL_ERR_RW_RETRIABLE(err))
			goto reschedule;

		what |= BEV_EVENT_ERROR;
	} else if (res == 0) {

		what |= BEV_EVENT_EOF;
	}

	if (res <= 0)
		goto error;

	bufferevent_decrement_read_buckets_(bufev_p, res);


	bufferevent_trigger_nolock_(bufev, EV_READ, 0);

	goto done;

 reschedule:
	goto done;

 error:
	bufferevent_disable(bufev, EV_READ);
	bufferevent_run_eventcb_(bufev, what, 0);

 done:
	bufferevent_decref_and_unlock_(bufev);
}
