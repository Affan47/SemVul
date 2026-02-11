dump_rdentry(int rdcounter, isc_uint64_t value, dns_rdatastatstype_t attributes,
	     dns_rdatatypestats_dumper_t dump_fn, void * arg)
{
	dns_rdatatype_t rdtype = dns_rdatatype_none;
	dns_rdatastatstype_t type;

	if (rdcounter == rdtypecounter_others)
		attributes |= DNS_RDATASTATSTYPE_ATTR_OTHERTYPE;
	else {
		if (rdcounter == rdtypecounter_dlv)
			rdtype = dns_rdatatype_dlv;
		else
			rdtype = (dns_rdatatype_t)rdcounter;
	}
	type = DNS_RDATASTATSTYPE_VALUE((dns_rdatastatstype_t)rdtype,
					attributes);
	dump_fn(type, value, arg);
}
