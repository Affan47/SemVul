find_entry(struct uip_stack *ustack,
					 struct in6_addr *addr6)
{
	int i;

	for (i = 0; i < UIP_NEIGHBOR_ENTRIES; ++i) {
		if (uip_ip6addr_cmp
		    (ustack->neighbor_entries[i].ipaddr.s6_addr,
		     addr6->s6_addr)) {
			return &ustack->neighbor_entries[i];
		}
	}

	return NULL;
}
