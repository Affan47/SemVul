event_base_foreach_event(struct event_base *base,
    event_base_foreach_event_cb fn, void *arg)
{
	int r;
	if ((!fn) || (!base)) {
		return -1;
	}
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	r = event_base_foreach_event_nolock_(base, fn, arg);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return r;
}
