be_get_wrb_params_from_skb(struct be_adapter *adapter,
				       struct sk_buff *skb,
				       struct be_wrb_params *wrb_params)
{
	u16 proto;

	if (skb_is_gso(skb)) {
		BE_WRB_F_SET(wrb_params->features, LSO, 1);
		wrb_params->lso_mss = skb_shinfo(skb)->gso_size;
		if (skb_is_gso_v6(skb) && !lancer_chip(adapter))
			BE_WRB_F_SET(wrb_params->features, LSO6, 1);
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (skb->encapsulation) {
			BE_WRB_F_SET(wrb_params->features, IPCS, 1);
			proto = skb_inner_ip_proto(skb);
		} else {
			proto = skb_ip_proto(skb);
		}
		if (proto == IPPROTO_TCP)
			BE_WRB_F_SET(wrb_params->features, TCPCS, 1);
		else if (proto == IPPROTO_UDP)
			BE_WRB_F_SET(wrb_params->features, UDPCS, 1);
	}

	if (skb_vlan_tag_present(skb)) {
		BE_WRB_F_SET(wrb_params->features, VLAN, 1);
		wrb_params->vlan_tag = be_get_tx_vlan_tag(adapter, skb);
	}

	BE_WRB_F_SET(wrb_params->features, CRC, 1);
}
