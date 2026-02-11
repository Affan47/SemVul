bufferevent_rate_limit_group_new(struct event_base *base,
    const struct ev_token_bucket_cfg *cfg)
{
	struct bufferevent_rate_limit_group *g;
	struct timeval now;
	ev_uint32_t tick;

	event_base_gettimeofday_cached(base, &now);
	tick = ev_token_bucket_get_tick(&now, cfg);

	g = mm_calloc(1, sizeof(struct bufferevent_rate_limit_group));
	if (!g)
		return NULL;
	memcpy(&g->rate_limit_cfg, cfg, sizeof(g->rate_limit_cfg));
	TAILQ_INIT(&g->members);

	ev_token_bucket_init(&g->rate_limit, cfg, tick, 0);

	g->min_share = 64;
	event_assign(&g->master_refill_event, base, -1, EV_PERSIST,
	    _bev_group_refill_callback, g);

	event_add(&g->master_refill_event, &cfg->tick_timeout);

	EVTHREAD_ALLOC_LOCK(g->lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	return g;
}
