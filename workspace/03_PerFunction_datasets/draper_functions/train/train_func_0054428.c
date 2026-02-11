dns_request_createraw2(dns_requestmgr_t *requestmgr, isc_buffer_t *msgbuf,
		       isc_sockaddr_t *srcaddr, isc_sockaddr_t *destaddr,
		       unsigned int options, unsigned int timeout,
		       unsigned int udptimeout, isc_task_t *task,
		       isc_taskaction_t action, void *arg,
		       dns_request_t **requestp)
{
	unsigned int udpretries = 0;

	if (udptimeout != 0)
		udpretries = timeout / udptimeout;

	return (dns_request_createraw3(requestmgr, msgbuf, srcaddr, destaddr,
				       options, timeout, udptimeout,
				       udpretries, task, action, arg,
				       requestp));
}
