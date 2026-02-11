kern_spec_to_ib_spec(struct ib_uverbs_flow_spec *kern_spec,
				union ib_flow_spec *ib_spec)
{
	if (kern_spec->reserved)
		return -EINVAL;

	ib_spec->type = kern_spec->type;

	switch (ib_spec->type) {
	case IB_FLOW_SPEC_ETH:
		ib_spec->eth.size = sizeof(struct ib_flow_spec_eth);
		if (ib_spec->eth.size != kern_spec->eth.size)
			return -EINVAL;
		memcpy(&ib_spec->eth.val, &kern_spec->eth.val,
		       sizeof(struct ib_flow_eth_filter));
		memcpy(&ib_spec->eth.mask, &kern_spec->eth.mask,
		       sizeof(struct ib_flow_eth_filter));
		break;
	case IB_FLOW_SPEC_IPV4:
		ib_spec->ipv4.size = sizeof(struct ib_flow_spec_ipv4);
		if (ib_spec->ipv4.size != kern_spec->ipv4.size)
			return -EINVAL;
		memcpy(&ib_spec->ipv4.val, &kern_spec->ipv4.val,
		       sizeof(struct ib_flow_ipv4_filter));
		memcpy(&ib_spec->ipv4.mask, &kern_spec->ipv4.mask,
		       sizeof(struct ib_flow_ipv4_filter));
		break;
	case IB_FLOW_SPEC_TCP:
	case IB_FLOW_SPEC_UDP:
		ib_spec->tcp_udp.size = sizeof(struct ib_flow_spec_tcp_udp);
		if (ib_spec->tcp_udp.size != kern_spec->tcp_udp.size)
			return -EINVAL;
		memcpy(&ib_spec->tcp_udp.val, &kern_spec->tcp_udp.val,
		       sizeof(struct ib_flow_tcp_udp_filter));
		memcpy(&ib_spec->tcp_udp.mask, &kern_spec->tcp_udp.mask,
		       sizeof(struct ib_flow_tcp_udp_filter));
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
