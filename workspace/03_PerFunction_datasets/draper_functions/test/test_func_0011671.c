dump_entry(FILE *f, dns_adbentry_t *entry, isc_boolean_t debug,
	   isc_stdtime_t now)
{
	char addrbuf[ISC_NETADDR_FORMATSIZE];
	char typebuf[DNS_RDATATYPE_FORMATSIZE];
	isc_netaddr_t netaddr;
	dns_adblameinfo_t *li;

	isc_netaddr_fromsockaddr(&netaddr, &entry->sockaddr);
	isc_netaddr_format(&netaddr, addrbuf, sizeof(addrbuf));

	if (debug)
		fprintf(f, ";\t%p: refcnt %u\n", entry, entry->refcnt);

	fprintf(f, ";\t%s [srtt %u] [flags %08x] [edns %u/%u/%u/%u/%u] "
		"[plain %u/%u]", addrbuf, entry->srtt, entry->flags,
		entry->edns, entry->to4096, entry->to1432, entry->to1232,
		entry->to512, entry->plain, entry->plainto);
	if (entry->udpsize != 0U)
		fprintf(f, " [udpsize %u]", entry->udpsize);
#ifdef ISC_PLATFORM_USESIT
	if (entry->sit != NULL) {
		unsigned int i;
		fprintf(f, " [sit=");
		for (i = 0; i < entry->sitlen; i++)
			fprintf(f, "%02x", entry->sit[i]);
		fprintf(f, "]");
	}
#endif

	if (entry->expires != 0)
		fprintf(f, " [ttl %d]", entry->expires - now);
	fprintf(f, "\n");
	for (li = ISC_LIST_HEAD(entry->lameinfo);
	     li != NULL;
	     li = ISC_LIST_NEXT(li, plink)) {
		fprintf(f, ";\t\t");
		print_dns_name(f, &li->qname);
		dns_rdatatype_format(li->qtype, typebuf, sizeof(typebuf));
		fprintf(f, " %s [lame TTL %d]\n", typebuf,
			li->lame_timer - now);
	}
}
