set_age(dns_rrl_t *rrl, dns_rrl_entry_t *e, isc_stdtime_t now) {
	dns_rrl_entry_t *e_old;
	unsigned int ts_gen;
	int i, ts;

	ts_gen = rrl->ts_gen;
	ts = now - rrl->ts_bases[ts_gen];
	if (ts < 0) {
		if (ts < -DNS_RRL_MAX_TIME_TRAVEL)
			ts = DNS_RRL_FOREVER;
		else
			ts = 0;
	}


	if (ts >= DNS_RRL_MAX_TS) {
		ts_gen = (ts_gen + 1) % DNS_RRL_TS_BASES;
		for (e_old = ISC_LIST_TAIL(rrl->lru), i = 0;
		     e_old != NULL && (e_old->ts_gen == ts_gen ||
				       !ISC_LINK_LINKED(e_old, hlink));
		     e_old = ISC_LIST_PREV(e_old, lru), ++i)
		{
			e_old->ts_valid = ISC_FALSE;
		}
		if (i != 0)
			isc_log_write(dns_lctx, DNS_LOGCATEGORY_RRL,
				      DNS_LOGMODULE_REQUEST, DNS_RRL_LOG_DEBUG1,
				      "rrl new time base scanned %d entries"
				      " at %d for %d %d %d %d",
				      i, now, rrl->ts_bases[ts_gen],
				      rrl->ts_bases[(ts_gen + 1) %
					DNS_RRL_TS_BASES],
				      rrl->ts_bases[(ts_gen + 2) %
					DNS_RRL_TS_BASES],
				      rrl->ts_bases[(ts_gen + 3) %
					DNS_RRL_TS_BASES]);
		rrl->ts_gen = ts_gen;
		rrl->ts_bases[ts_gen] = now;
		ts = 0;
	}

	e->ts_gen = ts_gen;
	e->ts = ts;
	e->ts_valid = ISC_TRUE;
}
