bufferevent_init_common(struct bufferevent_private *bufev_private,
    struct event_base *base,
    const struct bufferevent_ops *ops,
    enum bufferevent_options options)
{
	struct bufferevent *bufev = &bufev_private->bev;

	if (!bufev->input) {
		if ((bufev->input = evbuffer_new()) == NULL)
			return -1;
	}

	if (!bufev->output) {
		if ((bufev->output = evbuffer_new()) == NULL) {
			evbuffer_free(bufev->input);
			return -1;
		}
	}

	bufev_private->refcnt = 1;
	bufev->ev_base = base;


	evutil_timerclear(&bufev->timeout_read);
	evutil_timerclear(&bufev->timeout_write);

	bufev->be_ops = ops;


	bufev->enabled = EV_WRITE;

#ifndef _EVENT_DISABLE_THREAD_SUPPORT
	if (options & BEV_OPT_THREADSAFE) {
		if (bufferevent_enable_locking(bufev, NULL) < 0) {

			return -1;
		}
	}
#endif
	if (options & BEV_OPT_DEFER_CALLBACKS) {
		event_deferred_cb_init(&bufev_private->deferred,
		    bufferevent_run_deferred_callbacks,
		    bufev_private);
	}

	bufev_private->options = options;

	evbuffer_set_parent(bufev->input, bufev);
	evbuffer_set_parent(bufev->output, bufev);

	return 0;
}
