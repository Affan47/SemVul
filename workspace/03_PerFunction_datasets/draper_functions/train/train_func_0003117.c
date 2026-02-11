send_gssrequest(isc_sockaddr_t *srcaddr, isc_sockaddr_t *destaddr,
		dns_message_t *msg, dns_request_t **request,
		gss_ctx_id_t context)
{
	isc_result_t result;
	nsu_gssinfo_t *reqinfo;
	unsigned int options = 0;

	debug("send_gssrequest");
	reqinfo = isc_mem_get(mctx, sizeof(nsu_gssinfo_t));
	if (reqinfo == NULL)
		fatal("out of memory");
	reqinfo->msg = msg;
	reqinfo->addr = destaddr;
	reqinfo->context = context;

	options |= DNS_REQUESTOPT_TCP;
	result = dns_request_createvia3(requestmgr, msg, srcaddr, destaddr,
					options, tsigkey, FIND_TIMEOUT * 20,
					FIND_TIMEOUT, 3, global_task, recvgss,
					reqinfo, request);
	check_result(result, "dns_request_createvia3");
	if (debugging)
		show_message(stdout, msg, "Outgoing update query:");
	requests++;
}
