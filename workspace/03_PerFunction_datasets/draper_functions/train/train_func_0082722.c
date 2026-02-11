set_nport(struct sockaddr *sa, unsigned port)
{
#if ENABLE_FEATURE_IPV6
	if (sa->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6 = (void*) sa;
		sin6->sin6_port = port;
		return;
	}
#endif
	if (sa->sa_family == AF_INET) {
		struct sockaddr_in *sin = (void*) sa;
		sin->sin_port = port;
		return;
	}

}
