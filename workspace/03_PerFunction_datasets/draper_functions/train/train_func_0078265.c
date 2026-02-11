ixfr_apply(dns_xfrin_ctx_t *xfr) {
	isc_result_t result;

	if (xfr->ver == NULL) {
		CHECK(dns_db_newversion(xfr->db, &xfr->ver));
		if (xfr->ixfr.journal != NULL)
			CHECK(dns_journal_begin_transaction(xfr->ixfr.journal));
	}
	CHECK(dns_diff_apply(&xfr->diff, xfr->db, xfr->ver));
	if (xfr->ixfr.journal != NULL) {
		result = dns_journal_writediff(xfr->ixfr.journal, &xfr->diff);
		if (result != ISC_R_SUCCESS)
			goto failure;
	}
	dns_diff_clear(&xfr->diff);
	xfr->difflen = 0;
	result = ISC_R_SUCCESS;
 failure:
	return (result);
}
