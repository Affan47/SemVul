ones_complement_checksum(const ip* ipv4, const tcphdr* tcp,
                                         int tcp_len)
	{
	uint32_t sum;
	int payload_len = tcp_len - (tcp->th_off * 4);
	sum = ones_complement_checksum(&ipv4->ip_src, 4, 0);
	sum = ones_complement_checksum(&ipv4->ip_dst, 4, sum);
	sum += htons(IPPROTO_TCP);

	if ( payload_len % 2 == 1 )

		sum += htons(reinterpret_cast<const u_char*>(tcp)[tcp_len - 1] << 8);

	sum += htons(static_cast<u_short>(tcp_len));
	sum = ones_complement_checksum(tcp, tcp_len, sum);
	return sum;
	}
