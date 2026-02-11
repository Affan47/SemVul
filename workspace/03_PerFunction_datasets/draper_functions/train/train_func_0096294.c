ipv6_ip_in_arp_table(struct ipv6_context *context,
			 struct ipv6_addr *ip_addr,
			 struct mac_address *mac_addr)
{
	struct ipv6_arp_entry *arp_entry;
	int i;

	for (i = 0; i < UIP_ARPTAB_SIZE; i++) {
		arp_entry = &context->ipv6_arp_table[i];

		if (IPV6_ARE_ADDR_EQUAL(&arp_entry->ip_addr, ip_addr)) {
			memcpy((char *)mac_addr, &arp_entry->mac_addr,
			       sizeof(struct mac_address));
			return 1;
		}
	}
	return 0;
}
