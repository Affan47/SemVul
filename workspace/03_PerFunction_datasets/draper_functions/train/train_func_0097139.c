mark_related(dns_name_t *name, dns_rdataset_t *rdataset,
	     isc_boolean_t external, isc_boolean_t gluing)
{
	name->attributes |= DNS_NAMEATTR_CACHE;
	if (gluing) {
		rdataset->trust = dns_trust_glue;


		if (rdataset->ttl == 0)
			rdataset->ttl = 1;
	} else
		rdataset->trust = dns_trust_additional;


	if (!CACHE(rdataset)) {
		name->attributes |= DNS_NAMEATTR_CHASE;
		rdataset->attributes |= DNS_RDATASETATTR_CHASE;
	}
	rdataset->attributes |= DNS_RDATASETATTR_CACHE;
	if (external)
		rdataset->attributes |= DNS_RDATASETATTR_EXTERNAL;
}
