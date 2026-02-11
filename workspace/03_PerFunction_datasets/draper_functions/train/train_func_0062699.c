timer_handle_expirations(void)
{
	struct timeval  now;
	struct event   *n;

	gettimeofday(&now, 0);
	for (n = TAILQ_FIRST(&events); n && timercmp(&now, &n->expiration, >=);
	    n = TAILQ_FIRST(&events)) {
		LOG_DBG((LOG_TIMER, 10,
		    "timer_handle_expirations: event %s(%p)", n->name,
		    n->arg));
		TAILQ_REMOVE(&events, n, link);
		(*n->func)(n->arg);
		free(n);
	}
}
