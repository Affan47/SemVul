ones_complement_checksum(const ip* ipv4, const udphdr* udp,
                                         int udp_len)
	{
	uint32_t sum;

	if ( udp_len % 2 == 1 )

		sum = htons(reinterpret_cast<const u_char*>(udp)[udp_len - 1] << 8);
	else
		sum = 0;

	sum = ones_complement_checksum(&ipv4->ip_src, 4, sum);
	sum = ones_complement_checksum(&ipv4->ip_dst, 4, sum);
	sum += htons(IPPROTO_UDP);
	sum += htons(static_cast<u_short>(udp_len));
	sum = ones_complement_checksum(udp, udp_len, sum);
	return sum;
	}
