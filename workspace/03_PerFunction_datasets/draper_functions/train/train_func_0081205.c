udp_cksum(struct packhdr *hdr, const struct udphdr *u, u_int16_t *d, int af)
{
	struct ip	*ip4;
	struct ip6_hdr	*ip6;
	int	i, hdrlen, tlen = ntohs(u->uh_ulen) - sizeof(struct udphdr);

	union phu {
		struct ip4pseudo {
			struct in_addr  src;
			struct in_addr  dst;
			u_int8_t        z;
			u_int8_t        proto;
			u_int16_t       len;
		} ip4p;
		struct ip6pseudo {
			struct in6_addr src;
			struct in6_addr dst;
			u_int32_t       plen;
			u_int16_t       z0;
			u_int8_t        z1;
			u_int8_t        nxt;
		} ip6p;
		u_int16_t       pa[20];
	} phu;
	const u_int16_t *sp;
	u_int32_t       sum;


	memset(phu.pa, 0, sizeof phu);
	switch (af) {
	case AF_INET:
		ip4 = &hdr->ip.ip4;
		memcpy(&phu.ip4p.src, &ip4->ip_src, sizeof(struct in_addr));
		memcpy(&phu.ip4p.dst, &ip4->ip_dst, sizeof(struct in_addr));
		phu.ip4p.proto = ip4->ip_p;
		phu.ip4p.len = u->uh_ulen;
		hdrlen = sizeof phu.ip4p;
		break;

	case AF_INET6:
		ip6 = &hdr->ip.ip6;
		memcpy(&phu.ip6p.src, &ip6->ip6_src, sizeof(phu.ip6p.src));
		memcpy(&phu.ip6p.dst, &ip6->ip6_dst, sizeof(phu.ip6p.dst));
		phu.ip6p.plen = u->uh_ulen;
		phu.ip6p.nxt = ip6->ip6_nxt;
		hdrlen = sizeof phu.ip6p;
		break;

	default:
		return 0;
	}


	if (tlen < 0)
		return (af == AF_INET ? 0 : 0xFFFF);

	sum = 0;
	for (i = 0; i < hdrlen; i += 2)
		sum += phu.pa[i / 2];

	sp = (u_int16_t *) u;
	for (i = 0; i < (int)sizeof(struct udphdr); i += 2)
		sum += *sp++;

	sp = d;
	for (i = 0; i < (tlen & ~1); i += 2)
		sum += *sp++;

	if (tlen & 1)
		sum += htons((*(const char *)sp) << 8);

	while (sum > 0xffff)
		sum = (sum & 0xffff) + (sum >> 16);
	sum = ~sum & 0xffff;

	return sum;
}
