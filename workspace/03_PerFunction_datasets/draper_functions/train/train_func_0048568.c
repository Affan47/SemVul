update_rdatasetstats(dns_stats_t *stats, dns_rdatastatstype_t rrsettype,
		     isc_boolean_t increment)
{
	int counter;
	dns_rdatatype_t rdtype;

	if ((DNS_RDATASTATSTYPE_ATTR(rrsettype) &
	     DNS_RDATASTATSTYPE_ATTR_NXDOMAIN) != 0) {
		counter = rdtypecounter_nxdomain;
	} else {
		rdtype = DNS_RDATASTATSTYPE_BASE(rrsettype);
		if (rdtype == dns_rdatatype_dlv)
			counter = (int)rdtypecounter_dlv;
		else if (rdtype > dns_rdatatype_any)
			counter = (int)rdtypecounter_others;
		else
			counter = (int)rdtype;

		if ((DNS_RDATASTATSTYPE_ATTR(rrsettype) &
		     DNS_RDATASTATSTYPE_ATTR_NXRRSET) != 0)
			counter += rdtypecounter_max;
	}

	if (increment)
		isc_stats_increment(stats->counters, counter);
	else
		isc_stats_decrement(stats->counters, counter);
}
