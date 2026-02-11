event_config_set_max_dispatch_interval(struct event_config *cfg,
    const struct timeval *max_interval, int max_callbacks, int min_priority)
{
	if (max_interval)
		memcpy(&cfg->max_dispatch_interval, max_interval,
		    sizeof(struct timeval));
	else
		cfg->max_dispatch_interval.tv_sec = -1;
	cfg->max_dispatch_callbacks =
	    max_callbacks >= 0 ? max_callbacks : INT_MAX;
	if (min_priority < 0)
		min_priority = 0;
	cfg->limit_callbacks_after_prio = min_priority;
	return (0);
}
