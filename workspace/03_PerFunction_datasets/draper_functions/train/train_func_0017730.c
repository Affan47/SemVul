ip_checksum(void *buf, size_t len)
{
	struct ip_hdr *ip;
	int hl, off, sum;

	if (len < IP_HDR_LEN)
		return;

	ip = (struct ip_hdr *)buf;
	hl = ip->ip_hl << 2;
	ip->ip_sum = 0;
	sum = ip_cksum_add(ip, hl, 0);
	ip->ip_sum = ip_cksum_carry(sum);

	off = htons(ip->ip_off);

	if ((off & IP_OFFMASK) != 0 || (off & IP_MF) != 0)
		return;

	len -= hl;

	if (ip->ip_p == IP_PROTO_TCP) {
		struct tcp_hdr *tcp = (struct tcp_hdr *)((u_char *)ip + hl);

		if (len >= TCP_HDR_LEN) {
			tcp->th_sum = 0;
			sum = ip_cksum_add(tcp, len, 0) +
			    htons(ip->ip_p + len);
			sum = ip_cksum_add(&ip->ip_src, 8, sum);
			tcp->th_sum = ip_cksum_carry(sum);
		}
	} else if (ip->ip_p == IP_PROTO_UDP) {
		struct udp_hdr *udp = (struct udp_hdr *)((u_char *)ip + hl);

		if (len >= UDP_HDR_LEN) {
			udp->uh_sum = 0;
			sum = ip_cksum_add(udp, len, 0) +
			    htons(ip->ip_p + len);
			sum = ip_cksum_add(&ip->ip_src, 8, sum);
			udp->uh_sum = ip_cksum_carry(sum);
			if (!udp->uh_sum)
				udp->uh_sum = 0xffff;
		}
	} else if (ip->ip_p == IP_PROTO_ICMP || ip->ip_p == IP_PROTO_IGMP) {
		struct icmp_hdr *icmp = (struct icmp_hdr *)((u_char *)ip + hl);

		if (len >= ICMP_HDR_LEN) {
			icmp->icmp_cksum = 0;
			sum = ip_cksum_add(icmp, len, 0);
			icmp->icmp_cksum = ip_cksum_carry(sum);
		}
	}
}
