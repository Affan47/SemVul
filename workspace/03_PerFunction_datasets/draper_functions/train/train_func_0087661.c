check_throttles(connecttab * c)
{
	int		tnum;
	long		l;

	c->numtnums = 0;
	c->max_limit = c->min_limit = THROTTLE_NOLIMIT;
	for (tnum = 0; tnum < numthrottles && c->numtnums < MAXTHROTTLENUMS;
	     ++tnum)
		if (match(throttles[tnum].pattern, c->hc->expnfilename)) {

			if (throttles[tnum].rate > throttles[tnum].max_limit * 2)
				return 0;

			if (throttles[tnum].rate < throttles[tnum].min_limit)
				return 0;
			if (throttles[tnum].num_sending < 0) {
				syslog(LOG_ERR, "throttle sending count was negative - shouldn't happen!");
				throttles[tnum].num_sending = 0;
			}
			c->tnums[c->numtnums++] = tnum;
			++throttles[tnum].num_sending;
			l = throttles[tnum].max_limit / throttles[tnum].num_sending;
			if (c->max_limit == THROTTLE_NOLIMIT)
				c->max_limit = l;
			else
				c->max_limit = MIN(c->max_limit, l);
			l = throttles[tnum].min_limit;
			if (c->min_limit == THROTTLE_NOLIMIT)
				c->min_limit = l;
			else
				c->min_limit = MAX(c->min_limit, l);
		}
	return 1;
}
