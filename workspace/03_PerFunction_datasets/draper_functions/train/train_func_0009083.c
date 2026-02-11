event_base_gettimeofday_cached(struct event_base *base, struct timeval *tv)
{
	int r;
	if (!base) {
		base = current_base;
		if (!current_base)
			return evutil_gettimeofday(tv, NULL);
	}

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	if (base->tv_cache.tv_sec == 0) {
		r = evutil_gettimeofday(tv, NULL);
	} else {
#if defined(_EVENT_HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
		evutil_timeradd(&base->tv_cache, &base->tv_clock_diff, tv);
#else
		*tv = base->tv_cache;
#endif
		r = 0;
	}
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return r;
}
