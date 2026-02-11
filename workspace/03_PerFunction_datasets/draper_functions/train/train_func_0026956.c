tcpv4_bind_socket(int fd, int flags, struct sockaddr_in *local, struct sockaddr_in *remote)
{
	struct sockaddr_in bind_addr;
	int foreign_ok = 0;
	int ret;

#ifdef CONFIG_HAP_LINUX_TPROXY
	static int ip_transp_working = 1;
	if (flags && ip_transp_working) {
		if (setsockopt(fd, SOL_IP, IP_TRANSPARENT, (char *) &one, sizeof(one)) == 0
		    || setsockopt(fd, SOL_IP, IP_FREEBIND, (char *) &one, sizeof(one)) == 0)
			foreign_ok = 1;
		else
			ip_transp_working = 0;
	}
#endif
	if (flags) {
		memset(&bind_addr, 0, sizeof(bind_addr));
		bind_addr.sin_family = AF_INET;
		if (flags & 1)
			bind_addr.sin_addr = remote->sin_addr;
		if (flags & 2)
			bind_addr.sin_port = remote->sin_port;
	}

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &one, sizeof(one));
	if (foreign_ok) {
		ret = bind(fd, (struct sockaddr *)&bind_addr, sizeof(bind_addr));
		if (ret < 0)
			return 2;
	}
	else {
		ret = bind(fd, (struct sockaddr *)local, sizeof(*local));
		if (ret < 0)
			return 1;
	}

	if (!flags)
		return 0;

#ifdef CONFIG_HAP_CTTPROXY
	if (!foreign_ok) {
		struct in_tproxy itp1, itp2;
		memset(&itp1, 0, sizeof(itp1));

		itp1.op = TPROXY_ASSIGN;
		itp1.v.addr.faddr = bind_addr.sin_addr;
		itp1.v.addr.fport = bind_addr.sin_port;


		itp2.op = TPROXY_FLAGS;
		itp2.v.flags = ITP_CONNECT | ITP_ONCE;

		if (setsockopt(fd, SOL_IP, IP_TPROXY, &itp1, sizeof(itp1)) != -1 &&
		    setsockopt(fd, SOL_IP, IP_TPROXY, &itp2, sizeof(itp2)) != -1) {
			foreign_ok = 1;
		}
	}
#endif
	if (!foreign_ok)

		return 2;

	return 0;
}
