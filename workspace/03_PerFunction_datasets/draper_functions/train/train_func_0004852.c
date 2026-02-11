addr_map_entry_match_up_and_usable(addr_map_entry_t *a,
											   addr_map_entry_t *b)
{
	return iface_entry_up_and_usable(b->iface) &&
		   a->ip->ip_equals(a->ip, b->ip);
}
