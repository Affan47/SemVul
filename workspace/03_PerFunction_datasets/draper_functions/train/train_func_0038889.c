sifdefaultroute (int unit, int gateway)
{
	struct rtentry rt;

	if (has_default_route == 0) {
		if (defaultroute_exists())
			return 0;

		memset (&rt, '\0', sizeof (rt));
		SET_SA_FAMILY (rt.rt_dst,     AF_INET);
		SET_SA_FAMILY (rt.rt_gateway, AF_INET);
		((struct sockaddr_in *) &rt.rt_gateway)->sin_addr.s_addr = gateway;

		rt.rt_flags = RTF_UP | RTF_GATEWAY;
		if (ioctl(sockfd, SIOCADDRT, &rt) < 0) {
			int severity;


			if (errno == EEXIST) {
				severity = LOG_NOTICE;
			}
			else {
				severity = LOG_ERR;
			}
			syslog (severity, "default route ioctl(SIOCADDRT): %m");
			if (severity == LOG_ERR)
				return 0;
		}
	}
	has_default_route = 1;
	return 1;
}
