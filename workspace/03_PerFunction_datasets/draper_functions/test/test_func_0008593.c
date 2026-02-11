triededns(fetchctx_t *fctx, isc_sockaddr_t *address) {
	isc_sockaddr_t *sa;

	for (sa = ISC_LIST_HEAD(fctx->edns);
	     sa != NULL;
	     sa = ISC_LIST_NEXT(sa, link)) {
		if (isc_sockaddr_equal(sa, address))
			return (ISC_TRUE);
	}

	return (ISC_FALSE);
}
