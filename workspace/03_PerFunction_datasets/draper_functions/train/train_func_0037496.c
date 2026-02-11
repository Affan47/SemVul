netvsc_alloc_recv_skb(struct net_device *net,
				struct hv_netvsc_packet *packet,
				struct ndis_tcp_ip_checksum_info *csum_info,
				void *data, u16 vlan_tci)
{
	struct sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(net, packet->total_data_buflen);
	if (!skb)
		return skb;


	memcpy(skb_put(skb, packet->total_data_buflen), data,
	       packet->total_data_buflen);

	skb->protocol = eth_type_trans(skb, net);


	skb_checksum_none_assert(skb);


	if (csum_info && (net->features & NETIF_F_RXCSUM)) {
		if (csum_info->receive.tcp_checksum_succeeded ||
		    csum_info->receive.udp_checksum_succeeded)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	if (vlan_tci & VLAN_TAG_PRESENT)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       vlan_tci);

	return skb;
}
