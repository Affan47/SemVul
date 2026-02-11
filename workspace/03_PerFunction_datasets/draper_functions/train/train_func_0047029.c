identification_create_from_sockaddr(sockaddr_t *sockaddr)
{
	switch (sockaddr->sa_family)
	{
		case AF_INET:
		{
			struct in_addr *addr = &(((struct sockaddr_in*)sockaddr)->sin_addr);

			return identification_create_from_encoding(ID_IPV4_ADDR,
					chunk_create((u_char*)addr, sizeof(struct in_addr)));
		}
		case AF_INET6:
		{
			struct in6_addr *addr = &(((struct sockaddr_in6*)sockaddr)->sin6_addr);

			return identification_create_from_encoding(ID_IPV6_ADDR,
					chunk_create((u_char*)addr, sizeof(struct in6_addr)));
		}
		default:
		{
			private_identification_t *this = identification_create(ID_ANY);

			return &(this->public);
		}
	}
}
