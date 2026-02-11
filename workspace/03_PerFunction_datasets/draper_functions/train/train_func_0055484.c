print_ni_noop(struct iface_data *idata, const u_char *pktdata, struct pcap_pkthdr * pkthdr){
	struct ether_header 	*pkt_ether;
	struct ip6_hdr 			*pkt_ipv6;
	struct icmp6_nodeinfo	*pkt_ni;
	unsigned char			*pkt_end;

	pkt_ether = (struct ether_header *) pktdata;
	pkt_ipv6 = (struct ip6_hdr *)((char *) pkt_ether + idata->linkhsize);
	pkt_ni= (struct icmp6_nodeinfo *) ((char *) pkt_ipv6 + sizeof(struct ip6_hdr));
	pkt_end = (unsigned char *) pktdata + pkthdr->caplen;

	if( pkt_end > ((unsigned char *)pkt_ni + pkt_ipv6->ip6_plen) )
		pkt_end = (unsigned char *)pkt_ni + pkt_ipv6->ip6_plen;

	if(!is_eq_in6_addr(&(pkt_ipv6->ip6_dst), &(idata->srcaddr)))
		return 0;

	if(inet_ntop(AF_INET6, &(pkt_ipv6->ip6_src), pv6addr, sizeof(pv6addr)) == NULL){
		if(idata->verbose_f)
			puts("inet_ntop(): Error converting IPv6 Source Address to presentation format");

		return(-1);
	}

	printf("Response from: %s\n", pv6addr);

	switch(pkt_ni->ni_code){
		case 0:
			puts("\tCode: 0 (Successful reply)\n");
			break;

		case 1:
			puts("\tCode: 1 (Node refuses to supply the answer)\n");
			break;

		case 2:
			puts("\tCode: 2 (Qtype unknown to the responder)\n");
			break;

		default:
			printf("\tCode: %u (Qtype unknown)\n\n", pkt_ni->ni_code);
			break;
	}

	return(0);
}
