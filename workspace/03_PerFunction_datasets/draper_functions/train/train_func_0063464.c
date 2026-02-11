ping(len_and_sockaddr *lsa)
{
	printf("PING %s (%s)", hostname, dotted);
	if (source_lsa) {
		printf(" from %s",
			xmalloc_sockaddr2dotted_noport(&source_lsa->u.sa));
	}
	printf(": %d data bytes\n", datalen);

	G.sizeof_rcv_packet = datalen + MAXIPLEN + MAXICMPLEN;
	G.rcv_packet = xzalloc(G.sizeof_rcv_packet);
#if ENABLE_PING6
	if (lsa->u.sa.sa_family == AF_INET6) {


		G.snd_packet = xzalloc(datalen + sizeof(struct icmp6_hdr) + 4);
		ping6(lsa);
	} else
#endif
	{
		G.snd_packet = xzalloc(datalen + ICMP_MINLEN + 4);
		ping4(lsa);
	}
}
