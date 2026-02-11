new_adbaddrinfo(dns_adb_t *adb, dns_adbentry_t *entry, in_port_t port) {
	dns_adbaddrinfo_t *ai;

	ai = isc_mempool_get(adb->aimp);
	if (ai == NULL)
		return (NULL);

	ai->magic = DNS_ADBADDRINFO_MAGIC;
	ai->sockaddr = entry->sockaddr;
	isc_sockaddr_setport(&ai->sockaddr, port);
	ai->srtt = entry->srtt;
	ai->flags = entry->flags;
	ai->entry = entry;
	ai->dscp = -1;
	ISC_LINK_INIT(ai, publink);

	return (ai);
}
