get_net_transport_info(struct sk_buff *skb, u32 *trans_off)
{
	u32 ret_val = TRANSPORT_INFO_NOT_IP;

	if ((eth_hdr(skb)->h_proto != htons(ETH_P_IP)) &&
		(eth_hdr(skb)->h_proto != htons(ETH_P_IPV6))) {
		goto not_ip;
	}

	*trans_off = skb_transport_offset(skb);

	if ((eth_hdr(skb)->h_proto == htons(ETH_P_IP))) {
		struct iphdr *iphdr = ip_hdr(skb);

		if (iphdr->protocol == IPPROTO_TCP)
			ret_val = TRANSPORT_INFO_IPV4_TCP;
		else if (iphdr->protocol == IPPROTO_UDP)
			ret_val = TRANSPORT_INFO_IPV4_UDP;
	} else {
		if (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
			ret_val = TRANSPORT_INFO_IPV6_TCP;
		else if (ipv6_hdr(skb)->nexthdr == IPPROTO_UDP)
			ret_val = TRANSPORT_INFO_IPV6_UDP;
	}

not_ip:
	return ret_val;
}
