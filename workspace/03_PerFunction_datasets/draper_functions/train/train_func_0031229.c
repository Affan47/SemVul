log_edns(fetchctx_t *fctx) {
	char domainbuf[DNS_NAME_FORMATSIZE];

	if (fctx->reason == NULL)
		return;

	dns_name_format(&fctx->domain, domainbuf, sizeof(domainbuf));
	isc_log_write(dns_lctx, DNS_LOGCATEGORY_EDNS_DISABLED,
		      DNS_LOGMODULE_RESOLVER, ISC_LOG_INFO,
		      "success resolving '%s' (in '%s'?) after %s",
		      fctx->info, domainbuf, fctx->reason);

	fctx->reason = NULL;
}
