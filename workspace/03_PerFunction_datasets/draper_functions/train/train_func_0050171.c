get_age(const dns_rrl_t *rrl, const dns_rrl_entry_t *e, isc_stdtime_t now) {
	if (!e->ts_valid)
		return (DNS_RRL_FOREVER);
	return (delta_rrl_time(e->ts + rrl->ts_bases[e->ts_gen], now));
}
