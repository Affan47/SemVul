eth_push ( struct net_device *netdev __unused,
		      struct io_buffer *iobuf, const void *ll_dest,
		      const void *ll_source, uint16_t net_proto ) {
	struct ethhdr *ethhdr = iob_push ( iobuf, sizeof ( *ethhdr ) );


	memcpy ( ethhdr->h_dest, ll_dest, ETH_ALEN );
	memcpy ( ethhdr->h_source, ll_source, ETH_ALEN );
	ethhdr->h_protocol = net_proto;

	return 0;
}
