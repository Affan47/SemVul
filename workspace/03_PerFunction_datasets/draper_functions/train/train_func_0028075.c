ebnet_find_multiplex_entry(const char *ipv6_address, const char *ipv4_address,
    int port, int family)
{
    EBNet_Socket_Entry *entry;


    if (ebnet_socket_entry_cache != NULL
	&& (family == PF_INET6 || family == PF_UNSPEC)
	&& strcasecmp(ebnet_socket_entry_cache->address, ipv6_address) == 0
	&& ebnet_socket_entry_cache->port == port
	&& !ebnet_socket_entry_cache->lost_sync) {
	return ebnet_socket_entry_cache;
    }
    if (ebnet_socket_entry_cache != NULL
	&& (family == PF_INET || family == PF_UNSPEC)
	&& strcasecmp(ebnet_socket_entry_cache->address, ipv4_address) == 0
	&& ebnet_socket_entry_cache->port == port
	&& !ebnet_socket_entry_cache->lost_sync) {
	return ebnet_socket_entry_cache;
    }


    for (entry = ebnet_socket_entries; entry != NULL; entry = entry->next) {
	if ((family == PF_INET6 || family == PF_UNSPEC)
	    && strcasecmp(entry->address, ipv6_address) == 0
	    && entry->port == port
	    && !entry->lost_sync) {
	    ebnet_socket_entry_cache = entry;
	    return entry;
	}
	if ((family == PF_INET || family == PF_UNSPEC)
	    && strcasecmp(entry->address, ipv4_address) == 0
	    && entry->port == port
	    && !entry->lost_sync) {
	    ebnet_socket_entry_cache = entry;
	    return entry;
	}
    }

    return NULL;
}
