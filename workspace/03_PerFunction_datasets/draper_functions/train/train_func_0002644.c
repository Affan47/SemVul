get_ipv4address(struct sockaddr * ss)
{
	if (ss->sa_family == AF_INET)
		return ntohl(((struct sockaddr_in *) ss)->sin_addr.s_addr);
	else if(ss->sa_family == AF_INET6) {
		return ntohl(((struct sockaddr_in6 *) ss)->sin6_addr.s6_addr32[3]);
	} else

		return (uint32_t) -2;
}
