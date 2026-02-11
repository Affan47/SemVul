plip_type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct ethhdr *eth;
	unsigned char *rawp;

	skb_reset_mac_header(skb);
	skb_pull(skb,dev->hard_header_len);
	eth = eth_hdr(skb);

	if(is_multicast_ether_addr(eth->h_dest))
	{
		if(ether_addr_equal_64bits(eth->h_dest, dev->broadcast))
			skb->pkt_type=PACKET_BROADCAST;
		else
			skb->pkt_type=PACKET_MULTICAST;
	}


	if (ntohs(eth->h_proto) >= ETH_P_802_3_MIN)
		return eth->h_proto;

	rawp = skb->data;


	if (*(unsigned short *)rawp == 0xFFFF)
		return htons(ETH_P_802_3);


	return htons(ETH_P_802_2);
}
