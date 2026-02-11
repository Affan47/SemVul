bufferevent_update_buckets(struct bufferevent_private *bev)
{

	struct timeval now;
	unsigned tick;
	event_base_gettimeofday_cached(bev->bev.ev_base, &now);
	tick = ev_token_bucket_get_tick_(&now, bev->rate_limiting->cfg);
	if (tick != bev->rate_limiting->limit.last_updated)
		ev_token_bucket_update_(&bev->rate_limiting->limit,
		    bev->rate_limiting->cfg, tick);
}
