ipp_cache_item_expired(const ipp_cache_t *ic, time_t seen, time_t now)
{
	time_delta_t d = delta_time(now, seen);
	return d < 0 || d > (time_delta_t) *ic->max_cache_time;
}
