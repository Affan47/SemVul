get_port(struct sockaddr * sa)
{
	switch (sa->sa_family) {
		case AF_INET6:
			return (ntohs(((struct sockaddr_in6 *) sa)->sin6_port));
			break;
		case AF_INET:
		default:
			return (ntohs(((struct sockaddr_in *) sa)->sin_port));
	}
}
