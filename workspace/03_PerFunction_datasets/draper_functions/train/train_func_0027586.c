generate_reply_servers_single(Servlet * j, FullPacket * k)
{
	char    src[INET_ADDRSTRLEN];
	int     sockfd;
	uint16_t bar;
	Packet  pr;
	unsigned char foo[sizeof(in_addr_t) + sizeof(uint16_t)];

	if (cmp_sockaddr(j, &(k->addr)) != 0)
	{
		memcpy(foo, &(j->client.sin_addr.s_addr), 4);
		generate_reply_servers_found = 1;
		bar = j->client.sin_port;
		memcpy(foo + 4, &bar, sizeof(uint16_t));

		fillin_packet(&pr, REPLY_SERVERS,
					  sizeof(in_addr_t) + sizeof(uint16_t),
					  k->packet->request_handle);
		sockfd = get_outgoing_socket();
		send_packet(sockfd, &k->addr, &pr, foo);
	}
	return FALSE;
}
