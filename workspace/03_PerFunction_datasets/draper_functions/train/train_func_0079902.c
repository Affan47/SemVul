bufferevent_writecb(evutil_socket_t fd, short event, void *arg)
{
	struct bufferevent *bufev = arg;
	struct bufferevent_private *bufev_p =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	int res = 0;
	short what = BEV_EVENT_WRITING;
	int connected = 0;
	ev_ssize_t atmost = -1;

	_bufferevent_incref_and_lock(bufev);

	if (event == EV_TIMEOUT) {
		what |= BEV_EVENT_TIMEOUT;
		goto error;
	}
	if (bufev_p->connecting) {
		int c = evutil_socket_finished_connecting(fd);


		if (bufev_p->connection_refused) {
		  bufev_p->connection_refused = 0;
		  c = -1;
		}

		if (c == 0)
			goto done;

		bufev_p->connecting = 0;
		if (c < 0) {
			event_del(&bufev->ev_write);
			event_del(&bufev->ev_read);
			_bufferevent_run_eventcb(bufev, BEV_EVENT_ERROR);
			goto done;
		} else {
			connected = 1;
#ifdef WIN32
			if (BEV_IS_ASYNC(bufev)) {
				event_del(&bufev->ev_write);
				bufferevent_async_set_connected(bufev);
				_bufferevent_run_eventcb(bufev,
						BEV_EVENT_CONNECTED);
				goto done;
			}
#endif
			_bufferevent_run_eventcb(bufev,
					BEV_EVENT_CONNECTED);
			if (!(bufev->enabled & EV_WRITE) ||
			    bufev_p->write_suspended) {
				event_del(&bufev->ev_write);
				goto done;
			}
		}
	}

	atmost = _bufferevent_get_write_max(bufev_p);

	if (bufev_p->write_suspended)
		goto done;

	if (evbuffer_get_length(bufev->output)) {
		evbuffer_unfreeze(bufev->output, 1);
		res = evbuffer_write_atmost(bufev->output, fd, atmost);
		evbuffer_freeze(bufev->output, 1);
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

		_bufferevent_decrement_write_buckets(bufev_p, res);
	}

	if (evbuffer_get_length(bufev->output) == 0) {
		event_del(&bufev->ev_write);
	}


	if ((res || !connected) &&
	    evbuffer_get_length(bufev->output) <= bufev->wm_write.low) {
		_bufferevent_run_writecb(bufev);
	}

	goto done;

 reschedule:
	if (evbuffer_get_length(bufev->output) == 0) {
		event_del(&bufev->ev_write);
	}
	goto done;

 error:
	bufferevent_disable(bufev, EV_WRITE);
	_bufferevent_run_eventcb(bufev, what);

 done:
	_bufferevent_decref_and_unlock(bufev);
}
