sendrequest(isc_sockaddr_t *srcaddr, isc_sockaddr_t *destaddr,
	    dns_message_t *msg, dns_request_t **request)
{
	isc_result_t result;
	nsu_requestinfo_t *reqinfo;

	reqinfo = isc_mem_get(mctx, sizeof(nsu_requestinfo_t));
	if (reqinfo == NULL)
		fatal("out of memory");
	reqinfo->msg = msg;
	reqinfo->addr = destaddr;
	result = dns_request_createvia3(requestmgr, msg, srcaddr, destaddr, 0,
					(userserver != NULL) ? tsigkey : NULL,
					FIND_TIMEOUT * 20, FIND_TIMEOUT, 3,
					global_task, recvsoa, reqinfo, request);
	check_result(result, "dns_request_createvia");
	requests++;
}
