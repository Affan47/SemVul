can_cache_be_updated(

	trx_i_s_cache_t*	cache)
{
	ullint	now;


#ifdef UNIV_SYNC_DEBUG
	ut_a(rw_lock_own(&cache->rw_lock, RW_LOCK_EX));
#endif

	now = ut_time_us(NULL);
	if (now - cache->last_read > CACHE_MIN_IDLE_TIME_US) {

		return(TRUE);
	}

	return(FALSE);
}
