SPF_request_new(SPF_server_t *spf_server)
{
	SPF_request_t	*sr;

	sr = (SPF_request_t *)malloc(sizeof(SPF_request_t));
	if (! sr)
		return sr;
	memset(sr, 0, sizeof(SPF_request_t));

	sr->spf_server = spf_server;
	sr->client_ver = AF_UNSPEC;
	sr->ipv4.s_addr = htonl(INADDR_ANY);
	sr->ipv6 = in6addr_any;

	return sr;
}
