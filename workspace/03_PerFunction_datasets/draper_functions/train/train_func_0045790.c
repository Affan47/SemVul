request_alloc_coa(REQUEST *request)
{
	if (!request || request->coa) return NULL;


	if ((request->packet->code != PW_AUTHENTICATION_REQUEST) &&
	    (request->packet->code != PW_ACCOUNTING_REQUEST)) return NULL;

	request->coa = request_alloc_fake(request);
	request->coa->packet->code = 0;
	request->coa->child_state = REQUEST_RUNNING;
	request->coa->proxy = rad_alloc(0);

	return request->coa;
}
