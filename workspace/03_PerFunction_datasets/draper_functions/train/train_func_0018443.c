validator_log(void *val, int level, const char *fmt, ...) {
	va_list ap;

	if (! isc_log_wouldlog(dns_lctx, level))
		return;

	va_start(ap, fmt);

	validator_logv(val, DNS_LOGCATEGORY_DNSSEC,
		       DNS_LOGMODULE_VALIDATOR, level, fmt, ap);
	va_end(ap);
}
