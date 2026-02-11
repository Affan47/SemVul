marksecure(dns_validatorevent_t *event) {
	dns_rdataset_settrust(event->rdataset, dns_trust_secure);
	if (event->sigrdataset != NULL)
		dns_rdataset_settrust(event->sigrdataset, dns_trust_secure);
	event->secure = ISC_TRUE;
}
