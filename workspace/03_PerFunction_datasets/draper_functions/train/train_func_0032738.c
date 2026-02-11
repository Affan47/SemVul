update_throttles(ClientData client_data, struct timeval *nowP)
{
	int		tnum      , tind;
	int		cnum;
	connecttab     *c;
	long		l;


	for (tnum = 0; tnum < numthrottles; ++tnum) {
		throttles[tnum].rate = (2 * throttles[tnum].rate + throttles[tnum].bytes_since_avg / THROTTLE_TIME) / 3;
		throttles[tnum].bytes_since_avg = 0;

		if (throttles[tnum].rate > throttles[tnum].max_limit && throttles[tnum].num_sending != 0) {
			if (throttles[tnum].rate > throttles[tnum].max_limit * 2)
				syslog(LOG_NOTICE, "throttle #%d '%.80s' rate %ld greatly exceeding limit %ld; %d sending", tnum, throttles[tnum].pattern, throttles[tnum].rate, throttles[tnum].max_limit, throttles[tnum].num_sending);
			else
				syslog(LOG_INFO, "throttle #%d '%.80s' rate %ld exceeding limit %ld; %d sending", tnum, throttles[tnum].pattern, throttles[tnum].rate, throttles[tnum].max_limit, throttles[tnum].num_sending);
		}
		if (throttles[tnum].rate < throttles[tnum].min_limit && throttles[tnum].num_sending != 0) {
			syslog(LOG_NOTICE, "throttle #%d '%.80s' rate %ld lower than minimum %ld; %d sending", tnum, throttles[tnum].pattern, throttles[tnum].rate, throttles[tnum].min_limit, throttles[tnum].num_sending);
		}
	}


	for (cnum = 0; cnum < max_connects; ++cnum) {
		c = &connects[cnum];
		if (c->conn_state == CNST_SENDING || c->conn_state == CNST_PAUSING) {
			c->max_limit = THROTTLE_NOLIMIT;
			for (tind = 0; tind < c->numtnums; ++tind) {
				tnum = c->tnums[tind];
				l = throttles[tnum].max_limit / throttles[tnum].num_sending;
				if (c->max_limit == THROTTLE_NOLIMIT)
					c->max_limit = l;
				else
					c->max_limit = MIN(c->max_limit, l);
			}
		}
	}
}
