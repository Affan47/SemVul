add_question(dns_message_t *message, dns_name_t *name,
	     dns_rdataclass_t rdclass, dns_rdatatype_t rdtype)
{
	dns_rdataset_t *rdataset;
	isc_result_t result;

	debug("add_question()");
	rdataset = NULL;
	result = dns_message_gettemprdataset(message, &rdataset);
	check_result(result, "dns_message_gettemprdataset()");
	dns_rdataset_init(rdataset);
	dns_rdataset_makequestion(rdataset, rdclass, rdtype);
	ISC_LIST_APPEND(name->list, rdataset, link);
}
