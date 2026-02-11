sockaddr_addrdata(struct sockaddr *sa)
{
	switch (sa->sa_family) {
	case AF_INET6:
		return (u_int8_t *)&((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr;
	case AF_INET:
		return (u_int8_t *)&((struct sockaddr_in *)sa)->sin_addr.s_addr;
	default:
		log_print("sockaddr_addrdata: unsupported protocol family %d",
		    sa->sa_family);
		return 0;
	}
}
