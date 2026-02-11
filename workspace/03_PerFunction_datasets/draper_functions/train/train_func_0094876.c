event_base_active_by_signal(struct event_base *base, int sig)
{
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	evmap_signal_active_(base, sig, 1);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}
