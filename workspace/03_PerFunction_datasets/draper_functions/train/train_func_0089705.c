lookup_addr(struct addrinfo **res, int family, const char *host,
			const char *service, int passive)
{
	struct addrinfo hints = {
		.ai_family = family,
		.ai_socktype = SOCK_STREAM
	};

	if (passive)
		hints.ai_flags |= AI_PASSIVE;
	if (service == NULL)
		service="0";
	return eai_to_errno(getaddrinfo(host, service, &hints, res));
}
