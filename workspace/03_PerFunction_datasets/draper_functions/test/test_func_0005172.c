_bufferevent_decref_and_unlock(struct bufferevent *bufev)
{
	struct bufferevent_private *bufev_private =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	struct bufferevent *underlying;

	EVUTIL_ASSERT(bufev_private->refcnt > 0);

	if (--bufev_private->refcnt) {
		BEV_UNLOCK(bufev);
		return 0;
	}

	underlying = bufferevent_get_underlying(bufev);


	if (bufev->be_ops->destruct)
		bufev->be_ops->destruct(bufev);


	evbuffer_free(bufev->input);
	evbuffer_free(bufev->output);

	if (bufev_private->rate_limiting) {
		if (bufev_private->rate_limiting->group)
			bufferevent_remove_from_rate_limit_group_internal(bufev,0);
		if (event_initialized(&bufev_private->rate_limiting->refill_bucket_event))
			event_del(&bufev_private->rate_limiting->refill_bucket_event);
		event_debug_unassign(&bufev_private->rate_limiting->refill_bucket_event);
		mm_free(bufev_private->rate_limiting);
		bufev_private->rate_limiting = NULL;
	}

	event_debug_unassign(&bufev->ev_read);
	event_debug_unassign(&bufev->ev_write);

	BEV_UNLOCK(bufev);
	if (bufev_private->own_lock)
		EVTHREAD_FREE_LOCK(bufev_private->lock,
		    EVTHREAD_LOCKTYPE_RECURSIVE);


	mm_free(((char*)bufev) - bufev->be_ops->mem_offset);


	if (underlying)
		bufferevent_decref(underlying);

	return 1;
}
