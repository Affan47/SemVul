proxy_check_cache(u_int cl)
{
	struct proxy_private *mydata = cldata[cl].instance->data;
	struct proxylog **last, *pl;
	time_t now = time(NULL);

	if (mydata->lifetime == 0)
	{
		return 0;
	}

	DebugLog((ALOG_DSOCKSC, 0,
		"webproxy_check_cache(%d): Checking cache for %s",
		cl, cldata[cl].itsip));

	last = &(mydata->cache);
	while ((pl = *last))
	{
		DebugLog((ALOG_DSOCKSC, 0, "webproxy_check_cache(%d): cache %s",
			cl, pl->ip));
		if (pl->expire < now)
		{
			DebugLog((ALOG_DSOCKSC, 0,
				"webproxy_check_cache(%d): free %s (%d < %d)",
				cl, pl->ip, pl->expire, now));
			*last = pl->next;
			free(pl);
			mydata->cnow -= 1;
			continue;
		}
		if (!strcasecmp(pl->ip, cldata[cl].itsip))
		{
			DebugLog((ALOG_DSOCKSC, 0,
				"webproxy_check_cache(%d): match (%u)",
				cl, pl->state));
			pl->expire = now + mydata->lifetime;
			if (pl->state == 1)
			{
				proxy_open_proxy(cl);
				mydata->chito += 1;
			}
			else if (pl->state == 0)
			{
				mydata->chitn += 1;
			}
			else
			{
				mydata->chitc += 1;
			}
			return -1;
		}
		last = &(pl->next);
	}
	mydata->cmiss += 1;
	return 0;
}
