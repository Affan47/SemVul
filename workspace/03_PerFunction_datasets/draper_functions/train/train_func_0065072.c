wouldvalidate(fetchctx_t *fctx) {
	isc_boolean_t secure_domain;
	isc_result_t result;

	if (!fctx->res->view->enablevalidation)
		return (ISC_FALSE);

	if (fctx->res->view->dlv != NULL)
		return (ISC_TRUE);

	result = dns_view_issecuredomain(fctx->res->view, &fctx->name,
					 &secure_domain);
	if (result != ISC_R_SUCCESS)
		return (ISC_FALSE);
	return (secure_domain);
}
