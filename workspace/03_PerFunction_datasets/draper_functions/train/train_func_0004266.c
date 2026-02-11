axfr_makedb(dns_xfrin_ctx_t *xfr, dns_db_t **dbp) {
	isc_result_t result;

	result = dns_db_create(xfr->mctx,
			       "rbt",
			       &xfr->name,
			       dns_dbtype_zone,
			       xfr->rdclass,
			       0, NULL,
			       dbp);
	if (result == ISC_R_SUCCESS)
		result = dns_zone_rpz_enable_db(xfr->zone, *dbp);
	return (result);
}
