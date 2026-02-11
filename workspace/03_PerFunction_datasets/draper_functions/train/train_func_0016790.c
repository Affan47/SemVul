packet4_ok(int read_len, const struct sockaddr_in *from, int seq)
{
	const struct icmp *icp;
	unsigned char type, code;
	int hlen;
	const struct ip *ip;

	ip = (struct ip *) recv_pkt;
	hlen = ip->ip_hl << 2;
	if (read_len < hlen + ICMP_MINLEN) {
#if ENABLE_FEATURE_TRACEROUTE_VERBOSE
		if (verbose)
			printf("packet too short (%d bytes) from %s\n", read_len,
				inet_ntoa(from->sin_addr));
#endif
		return 0;
	}
	read_len -= hlen;
	icp = (struct icmp *)(recv_pkt + hlen);
	type = icp->icmp_type;
	code = icp->icmp_code;

	pmtu = 0;
	if (code == ICMP_UNREACH_NEEDFRAG)
		pmtu = ntohs(icp->icmp_nextmtu);

	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS)
	 || type == ICMP_UNREACH
	 || type == ICMP_ECHOREPLY
	) {
		const struct ip *hip;
		const struct udphdr *up;

		hip = &icp->icmp_ip;
		hlen = hip->ip_hl << 2;
		if (option_mask32 & OPT_USE_ICMP) {
			struct icmp *hicmp;


			if (type == ICMP_ECHOREPLY
			 && icp->icmp_id == htons(ident)
			 && icp->icmp_seq == htons(seq)
			) {
				return ICMP_UNREACH_PORT+1;
			}

			hicmp = (struct icmp *)((unsigned char *)hip + hlen);
			if (hlen + SIZEOF_ICMP_HDR <= read_len
			 && hip->ip_p == IPPROTO_ICMP
			 && hicmp->icmp_id == htons(ident)
			 && hicmp->icmp_seq == htons(seq)
			) {
				return (type == ICMP_TIMXCEED ? -1 : code + 1);
			}
		} else {
			up = (struct udphdr *)((char *)hip + hlen);
			if (hlen + 12 <= read_len
			 && hip->ip_p == IPPROTO_UDP


			 && up->dest == htons(port + seq)
			) {
				return (type == ICMP_TIMXCEED ? -1 : code + 1);
			}
		}
	}
#if ENABLE_FEATURE_TRACEROUTE_VERBOSE
	if (verbose) {
		int i;
		uint32_t *lp = (uint32_t *)&icp->icmp_ip;

		printf("\n%d bytes from %s to "
		       "%s: icmp type %d (%s) code %d\n",
			read_len, inet_ntoa(from->sin_addr),
			inet_ntoa(ip->ip_dst),
			type, pr_type(type), icp->icmp_code);
		for (i = 4; i < read_len; i += sizeof(*lp))
			printf("%2d: x%8.8x\n", i, *lp++);
	}
#endif
	return 0;
}
