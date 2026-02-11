udpfromto_init(int s)
{
	int proto, flag, opt = 1;
	struct sockaddr_storage si;
	socklen_t si_len = sizeof(si);

	errno = ENOSYS;

	proto = -1;

	if (getsockname(s, (struct sockaddr *) &si, &si_len) < 0) {
		return -1;
	}

	if (si.ss_family == AF_INET) {
#ifdef HAVE_IP_PKTINFO


		proto = SOL_IP;
		flag = IP_PKTINFO;
#endif

#ifdef IP_RECVDSTADDR


		proto = IPPROTO_IP;
		flag = IP_RECVDSTADDR;
#endif

#ifdef AF_INET6
	} else if (si.ss_family == AF_INET6) {
#ifdef IPV6_PKTINFO


		proto = IPPROTO_IPV6;


		flag = FR_IPV6_RECVPKTINFO;
#endif
#endif
	} else {


		return -1;
	}


	if (proto < 0) return 0;

	return setsockopt(s, proto, flag, &opt, sizeof(opt));
}
