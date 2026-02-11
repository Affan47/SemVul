ipv6_is_it_our_address(struct ipv6_context *context,
				  struct ipv6_addr *ipv6_addr)
{
	struct ipv6_prefix_entry *ipv6_prefix;

	for (ipv6_prefix = context->addr_list; ipv6_prefix != NULL;
	     ipv6_prefix = ipv6_prefix->next) {
		if (IPV6_ARE_ADDR_EQUAL(&ipv6_prefix->ip_addr, ipv6_addr))
			return TRUE;
	}

	return FALSE;
}
