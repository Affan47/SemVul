niu_compute_tx_flags(struct sk_buff *skb, struct ethhdr *ehdr,
				u64 pad_bytes, u64 len)
{
	u16 eth_proto, eth_proto_inner;
	u64 csum_bits, l3off, ihl, ret;
	u8 ip_proto;
	int ipv6;

	eth_proto = be16_to_cpu(ehdr->h_proto);
	eth_proto_inner = eth_proto;
	if (eth_proto == ETH_P_8021Q) {
		struct vlan_ethhdr *vp = (struct vlan_ethhdr *) ehdr;
		__be16 val = vp->h_vlan_encapsulated_proto;

		eth_proto_inner = be16_to_cpu(val);
	}

	ipv6 = ihl = 0;
	switch (skb->protocol) {
	case cpu_to_be16(ETH_P_IP):
		ip_proto = ip_hdr(skb)->protocol;
		ihl = ip_hdr(skb)->ihl;
		break;
	case cpu_to_be16(ETH_P_IPV6):
		ip_proto = ipv6_hdr(skb)->nexthdr;
		ihl = (40 >> 2);
		ipv6 = 1;
		break;
	default:
		ip_proto = ihl = 0;
		break;
	}

	csum_bits = TXHDR_CSUM_NONE;
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		u64 start, stuff;

		csum_bits = (ip_proto == IPPROTO_TCP ?
			     TXHDR_CSUM_TCP :
			     (ip_proto == IPPROTO_UDP ?
			      TXHDR_CSUM_UDP : TXHDR_CSUM_SCTP));

		start = skb_checksum_start_offset(skb) -
			(pad_bytes + sizeof(struct tx_pkt_hdr));
		stuff = start + skb->csum_offset;

		csum_bits |= (start / 2) << TXHDR_L4START_SHIFT;
		csum_bits |= (stuff / 2) << TXHDR_L4STUFF_SHIFT;
	}

	l3off = skb_network_offset(skb) -
		(pad_bytes + sizeof(struct tx_pkt_hdr));

	ret = (((pad_bytes / 2) << TXHDR_PAD_SHIFT) |
	       (len << TXHDR_LEN_SHIFT) |
	       ((l3off / 2) << TXHDR_L3START_SHIFT) |
	       (ihl << TXHDR_IHL_SHIFT) |
	       ((eth_proto_inner < ETH_P_802_3_MIN) ? TXHDR_LLC : 0) |
	       ((eth_proto == ETH_P_8021Q) ? TXHDR_VLAN : 0) |
	       (ipv6 ? TXHDR_IP_VER : 0) |
	       csum_bits);

	return ret;
}
