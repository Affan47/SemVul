_PR_ConvertToIpv6NetAddr(const PRNetAddr *src_v4addr,
                                            PRNetAddr *dst_v6addr)
{
PRUint8 *dstp;

	PR_ASSERT(PR_AF_INET == src_v4addr->inet.family);
	dst_v6addr->ipv6.family = PR_AF_INET6;
	dst_v6addr->ipv6.port = src_v4addr->inet.port;

 	if (htonl(INADDR_ANY) == src_v4addr->inet.ip) {
		dst_v6addr->ipv6.ip = _pr_in6addr_any;
	} else {
		dstp = dst_v6addr->ipv6.ip.pr_s6_addr;
		memset(dstp, 0, 10);
		memset(dstp + 10, 0xff, 2);
		memcpy(dstp + 12,(char *) &src_v4addr->inet.ip, 4);
	}
}
