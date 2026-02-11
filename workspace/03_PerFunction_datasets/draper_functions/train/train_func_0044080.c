issecuredomain(dns_view_t *view, dns_name_t *name, dns_rdatatype_t type,
	       isc_stdtime_t now, isc_boolean_t checknta,
	       isc_boolean_t *issecure)
{
	dns_name_t suffix;
	unsigned int labels;


	labels = dns_name_countlabels(name);
	if (dns_rdatatype_atparent(type) && labels > 1) {
		dns_name_init(&suffix, NULL);
		dns_name_getlabelsequence(name, 1, labels - 1, &suffix);
		name = &suffix;
	}

	return (dns_view_issecuredomain(view, name, now, checknta, issecure));
}
