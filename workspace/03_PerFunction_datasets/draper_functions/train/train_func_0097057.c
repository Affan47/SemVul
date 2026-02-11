xfrin_fail(dns_xfrin_ctx_t *xfr, isc_result_t result, const char *msg) {
	if (result != DNS_R_UPTODATE) {
		xfrin_log(xfr, ISC_LOG_ERROR, "%s: %s",
			  msg, isc_result_totext(result));
		if (xfr->is_ixfr)

			result = DNS_R_BADIXFR;
	}
	xfrin_cancelio(xfr);


	if (xfr->ixfr.journal != NULL)
		dns_journal_destroy(&xfr->ixfr.journal);
	if (xfr->done != NULL) {
		(xfr->done)(xfr->zone, result);
		xfr->done = NULL;
	}
	xfr->shuttingdown = ISC_TRUE;
	maybe_free(xfr);
}
