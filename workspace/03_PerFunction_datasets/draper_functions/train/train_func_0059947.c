calc_txpeerstamp(struct iax2_trunk_peer *tpeer, int sampms, struct timeval *now)
{
	unsigned long int mssincetx;
	long int ms, pred;

	tpeer->trunkact = *now;
	mssincetx = ast_tvdiff_ms(*now, tpeer->lasttxtime);
	if (mssincetx > 5000 || ast_tvzero(tpeer->txtrunktime)) {

		tpeer->txtrunktime = *now;
		tpeer->lastsent = 999999;
	}

	tpeer->lasttxtime = *now;


	ms = ast_tvdiff_ms(*now, tpeer->txtrunktime);

	pred = tpeer->lastsent + sampms;
	if (abs(ms - pred) < MAX_TIMESTAMP_SKEW)
		ms = pred;


	if (ms == tpeer->lastsent)
		ms = tpeer->lastsent + 1;
	tpeer->lastsent = ms;
	return ms;
}
