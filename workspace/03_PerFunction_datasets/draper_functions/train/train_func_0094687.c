get_dispatch(isc_boolean_t tcp, dns_requestmgr_t *requestmgr,
	     isc_sockaddr_t *srcaddr, isc_sockaddr_t *destaddr,
	     isc_dscp_t dscp, dns_dispatch_t **dispatchp)
{
	isc_result_t result;
	if (tcp)
		result = create_tcp_dispatch(requestmgr, srcaddr,
					     destaddr, dscp, dispatchp);
	else
		result = find_udp_dispatch(requestmgr, srcaddr,
					   destaddr, dispatchp);
	return (result);
}
