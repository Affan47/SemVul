fctx_addopt(dns_message_t *message, unsigned int version,
	    isc_uint16_t udpsize, isc_boolean_t request_nsid)
{
	dns_rdataset_t *rdataset;
	dns_rdatalist_t *rdatalist;
	dns_rdata_t *rdata;
	isc_result_t result;

	rdatalist = NULL;
	result = dns_message_gettemprdatalist(message, &rdatalist);
	if (result != ISC_R_SUCCESS)
		return (result);
	rdata = NULL;
	result = dns_message_gettemprdata(message, &rdata);
	if (result != ISC_R_SUCCESS)
		return (result);
	rdataset = NULL;
	result = dns_message_gettemprdataset(message, &rdataset);
	if (result != ISC_R_SUCCESS)
		return (result);
	dns_rdataset_init(rdataset);

	rdatalist->type = dns_rdatatype_opt;
	rdatalist->covers = 0;


	rdatalist->rdclass = udpsize;


	rdatalist->ttl = (version << 16);
	rdatalist->ttl |= DNS_MESSAGEEXTFLAG_DO;


	if (request_nsid) {

		unsigned char data[4];
		isc_buffer_t buf;

		isc_buffer_init(&buf, data, sizeof(data));
		isc_buffer_putuint16(&buf, DNS_OPT_NSID);
		isc_buffer_putuint16(&buf, 0);
		rdata->data = data;
		rdata->length = sizeof(data);
	} else {
		rdata->data = NULL;
		rdata->length = 0;
	}

	rdata->rdclass = rdatalist->rdclass;
	rdata->type = rdatalist->type;
	rdata->flags = 0;

	ISC_LIST_INIT(rdatalist->rdata);
	ISC_LIST_APPEND(rdatalist->rdata, rdata, link);
	RUNTIME_CHECK(dns_rdatalist_tordataset(rdatalist, rdataset) == ISC_R_SUCCESS);

	return (dns_message_setopt(message, rdataset));
}
