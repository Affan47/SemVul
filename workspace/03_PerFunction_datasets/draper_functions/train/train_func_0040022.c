net_client_lookup(const char *hostname,
				   const char *service,
				   int family,
				   int socktype)
{
	struct addrinfo hints;
	struct addrinfo *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if (getaddrinfo(hostname, service, &hints, &res) != 0)
		return NULL;

	return res;
}
