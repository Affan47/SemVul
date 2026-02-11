dcc_calc_cps (struct DCC *dcc)
{
	GTimeVal now;
	int oldcps;
	double timediff, startdiff;
	int glob_throttle_bit, wasthrottled;
	int *cpssum, glob_limit;
	DCC_SIZE pos, posdiff;

	g_get_current_time (&now);


	if (dcc->type == TYPE_SEND)
	{

		pos = dcc->pos - ((dcc->pos - dcc->ack) / 2);
		glob_throttle_bit = 0x1;
		cpssum = &dcc_sendcpssum;
		glob_limit = prefs.hex_dcc_global_max_send_cps;
	}
	else
	{
		pos = dcc->pos;
		glob_throttle_bit = 0x2;
		cpssum = &dcc_getcpssum;
		glob_limit = prefs.hex_dcc_global_max_get_cps;
	}

	if (!dcc->firstcpstv.tv_sec && !dcc->firstcpstv.tv_usec)
		dcc->firstcpstv = now;
	else
	{
		startdiff = timeval_diff (&now, &dcc->firstcpstv);
		if (startdiff < 1)
			startdiff = 1;
		else if (startdiff > CPS_AVG_WINDOW)
			startdiff = CPS_AVG_WINDOW;

		timediff = timeval_diff (&now, &dcc->lastcpstv);
		if (timediff > startdiff)
			timediff = startdiff = 1;

		posdiff = pos - dcc->lastcpspos;
		oldcps = dcc->cps;
		dcc->cps = ((double) posdiff / timediff) * (timediff / startdiff) +
			(double) dcc->cps * (1.0 - (timediff / startdiff));

		*cpssum += dcc->cps - oldcps;
	}

	dcc->lastcpspos = pos;
	dcc->lastcpstv = now;


	wasthrottled = dcc->throttled;


	dcc->throttled &= ~0x2;
	if (glob_limit > 0 && *cpssum >= glob_limit)
	{
		dcc_global_throttle |= glob_throttle_bit;
		if (dcc->maxcps >= 0)
			dcc->throttled |= 0x2;
	}
	else
		dcc_global_throttle &= ~glob_throttle_bit;


	if (dcc->maxcps > 0 && dcc->cps > dcc->maxcps)
		dcc->throttled |= 0x1;
	else
		dcc->throttled &= ~0x1;


	if (wasthrottled && !dcc->throttled)
		dcc_unthrottle (dcc);
}
