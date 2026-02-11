xfrin_log(dns_xfrin_ctx_t *xfr, int level, const char *fmt, ...)
{
	va_list ap;
	char zonetext[DNS_NAME_MAXTEXT+32];

	if (isc_log_wouldlog(dns_lctx, level) == ISC_FALSE)
		return;

	dns_zone_name(xfr->zone, zonetext, sizeof(zonetext));

	va_start(ap, fmt);
	xfrin_logv(level, zonetext, &xfr->masteraddr, fmt, ap);
	va_end(ap);
}
