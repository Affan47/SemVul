arp_rx ( struct io_buffer *iobuf, struct net_device *netdev,
		    const void *ll_dest __unused,
		    const void *ll_source __unused,
		    unsigned int flags __unused ) {
	struct arphdr *arphdr = iobuf->data;
	struct arp_net_protocol *arp_net_protocol;
	struct net_protocol *net_protocol;
	struct ll_protocol *ll_protocol;
	struct arp_entry *arp;
	int merge = 0;


	arp_net_protocol = arp_find_protocol ( arphdr->ar_pro );
	if ( ! arp_net_protocol )
		goto done;
	net_protocol = arp_net_protocol->net_protocol;
	ll_protocol = netdev->ll_protocol;


	if ( ( arphdr->ar_hrd != ll_protocol->ll_proto ) ||
	     ( arphdr->ar_hln != ll_protocol->ll_addr_len ) ||
	     ( arphdr->ar_pln != net_protocol->net_addr_len ) )
		goto done;


	arp = arp_find_entry ( ll_protocol, net_protocol,
			       arp_sender_pa ( arphdr ) );
	if ( arp ) {
		memcpy ( arp->ll_addr, arp_sender_ha ( arphdr ),
			 arphdr->ar_hln );
		merge = 1;
		DBG ( "ARP cache update: %s %s => %s %s\n",
		      net_protocol->name, net_protocol->ntoa ( arp->net_addr ),
		      ll_protocol->name, ll_protocol->ntoa ( arp->ll_addr ) );
	}


	if ( arp_net_protocol->check ( netdev, arp_target_pa ( arphdr ) ) != 0)
		goto done;


	if ( ! merge ) {
		arp = &arp_table[next_new_arp_entry++ % NUM_ARP_ENTRIES];
		arp->ll_protocol = ll_protocol;
		arp->net_protocol = net_protocol;
		memcpy ( arp->ll_addr, arp_sender_ha ( arphdr ),
			 arphdr->ar_hln );
		memcpy ( arp->net_addr, arp_sender_pa ( arphdr ),
			 arphdr->ar_pln);
		DBG ( "ARP cache add: %s %s => %s %s\n",
		      net_protocol->name, net_protocol->ntoa ( arp->net_addr ),
		      ll_protocol->name, ll_protocol->ntoa ( arp->ll_addr ) );
	}


	if ( arphdr->ar_op != htons ( ARPOP_REQUEST ) )
		goto done;


	DBG ( "ARP reply: %s %s => %s %s\n", net_protocol->name,
	      net_protocol->ntoa ( arp_target_pa ( arphdr ) ),
	      ll_protocol->name, ll_protocol->ntoa ( netdev->ll_addr ) );
	arphdr->ar_op = htons ( ARPOP_REPLY );
	memswap ( arp_sender_ha ( arphdr ), arp_target_ha ( arphdr ),
		 arphdr->ar_hln + arphdr->ar_pln );
	memcpy ( arp_sender_ha ( arphdr ), netdev->ll_addr, arphdr->ar_hln );


	net_tx ( iob_disown ( iobuf ), netdev, &arp_protocol,
		 arp_target_ha ( arphdr ), netdev->ll_addr );

 done:
	free_iob ( iobuf );
	return 0;
}
