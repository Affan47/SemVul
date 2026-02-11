ipv6_icmp_handle_router_adv(struct ipv6_context *context)
{
	struct ipv6_hdr *ipv6 =
			(struct ipv6_hdr *)context->ustack->network_layer;
	struct icmpv6_router_advert *icmp =
	(struct icmpv6_router_advert *)((u8_t *)ipv6 + sizeof(struct ipv6_hdr));
	struct icmpv6_opt_hdr *icmp_opt;
	u16_t opt_len;
	u16_t len;
	char addr_str[INET6_ADDRSTRLEN];

	if (context->flags & IPV6_FLAGS_ROUTER_ADV_RECEIVED)
		return;

	opt_len = HOST_TO_NET16(ipv6->ipv6_plen) -
		  sizeof(struct icmpv6_router_advert);

	icmp_opt = (struct icmpv6_opt_hdr *)((u8_t *)icmp +
				      sizeof(struct icmpv6_router_advert));
	len = 0;
	while (len < opt_len) {
		icmp_opt = (struct icmpv6_opt_hdr *)((u8_t *)icmp +
					sizeof(struct icmpv6_router_advert) +
					len);

		switch (icmp_opt->type) {
		case IPV6_ICMP_OPTION_PREFIX:
			ipv6_icmp_process_prefix(context,
					(struct icmpv6_opt_prefix *)icmp_opt);
			context->flags |= IPV6_FLAGS_ROUTER_ADV_RECEIVED;
			break;

		default:
			break;
		}

		len += icmp_opt->len * 8;
	}

	if (context->flags & IPV6_FLAGS_ROUTER_ADV_RECEIVED) {
		LOG_DEBUG("IPv6: RTR ADV nd_ra_flags = 0x%x",
			  icmp->nd_ra_flags_reserved);
		if (icmp->nd_ra_curhoplimit > 0)
			context->hop_limit = icmp->nd_ra_curhoplimit;

		if (icmp->nd_ra_flags_reserved & IPV6_RA_MANAGED_FLAG)
			context->flags |= IPV6_FLAGS_MANAGED_ADDR_CONFIG;

		if (icmp->nd_ra_flags_reserved & IPV6_RA_CONFIG_FLAG)
			context->flags |= IPV6_FLAGS_OTHER_STATEFUL_CONFIG;

		if (icmp->nd_ra_router_lifetime != 0) {

			if (context->ustack->router_autocfg !=
			    IPV6_RTR_AUTOCFG_OFF)
				memcpy(
				   (char *)&context->default_router,
				       (char *)&ipv6->ipv6_src,
				       sizeof(struct ipv6_addr));
			inet_ntop(AF_INET6, &context->default_router,
				  addr_str, sizeof(addr_str));
			LOG_DEBUG("IPv6: Got default router IP addr: %s",
				  addr_str);
		}
	}
}
