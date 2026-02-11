set_raw_socket_tos(evutil_socket_t fd, int family, int tos)
{

	if(family == AF_INET6) {
#if !defined(IPV6_RECVTCLASS)
		UNUSED_ARG(fd);
		UNUSED_ARG(tos);
#else
		CORRECT_RAW_TOS(tos);
		if(setsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &tos,sizeof(tos))<0) {
			perror("set TCLASS on socket");
			return -1;
		}
#endif
	} else {
#if !defined(IPV6_RECVTOS)
		UNUSED_ARG(fd);
		UNUSED_ARG(tos);
#else
		if(setsockopt(fd, IPPROTO_IP, IP_TOS, &tos,sizeof(tos))<0) {
			perror("set TOS on socket");
			return -1;
		}
#endif
	}

	return 0;
}
