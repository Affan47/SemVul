copy_name(isc_mem_t *mctx, dns_message_t *msg, dns_name_t *name,
	  dns_name_t **newnamep)
{
	isc_result_t result;
	dns_name_t *newname = NULL;
	isc_region_t r;
	isc_buffer_t *namebuf = NULL, *rdatabuf = NULL;
	dns_rdatalist_t *rdatalist;
	dns_rdataset_t *rdataset, *newrdataset;
	dns_rdata_t rdata = DNS_RDATA_INIT, *newrdata;

	result = dns_message_gettempname(msg, &newname);
	if (result != ISC_R_SUCCESS)
		return (result);
	result = isc_buffer_allocate(mctx, &namebuf, DNS_NAME_MAXWIRE);
	if (result != ISC_R_SUCCESS)
		goto fail;
	dns_name_init(newname, NULL);
	dns_name_setbuffer(newname, namebuf);
	dns_message_takebuffer(msg, &namebuf);
	result = dns_name_copy(name, newname, NULL);
	if (result != ISC_R_SUCCESS)
		goto fail;

	for (rdataset = ISC_LIST_HEAD(name->list); rdataset != NULL;
	     rdataset = ISC_LIST_NEXT(rdataset, link)) {
		rdatalist = NULL;
		result = dns_message_gettemprdatalist(msg, &rdatalist);
		if (result != ISC_R_SUCCESS)
			goto fail;
		dns_rdatalist_init(rdatalist);
		rdatalist->type = rdataset->type;
		rdatalist->rdclass = rdataset->rdclass;
		rdatalist->covers = rdataset->covers;
		rdatalist->ttl = rdataset->ttl;

		result = dns_rdataset_first(rdataset);
		while (result == ISC_R_SUCCESS) {
			dns_rdata_reset(&rdata);
			dns_rdataset_current(rdataset, &rdata);

			newrdata = NULL;
			result = dns_message_gettemprdata(msg, &newrdata);
			if (result != ISC_R_SUCCESS)
				goto fail;
			dns_rdata_toregion(&rdata, &r);
			rdatabuf = NULL;
			result = isc_buffer_allocate(mctx, &rdatabuf,
						     r.length);
			if (result != ISC_R_SUCCESS)
				goto fail;
			isc_buffer_putmem(rdatabuf, r.base, r.length);
			isc_buffer_usedregion(rdatabuf, &r);
			dns_rdata_init(newrdata);
			dns_rdata_fromregion(newrdata, rdata.rdclass,
					     rdata.type, &r);
			newrdata->flags = rdata.flags;

			ISC_LIST_APPEND(rdatalist->rdata, newrdata, link);
			dns_message_takebuffer(msg, &rdatabuf);

			result = dns_rdataset_next(rdataset);
		}

		newrdataset = NULL;
		result = dns_message_gettemprdataset(msg, &newrdataset);
		if (result != ISC_R_SUCCESS)
			goto fail;
		dns_rdataset_init(newrdataset);
		dns_rdatalist_tordataset(rdatalist, newrdataset);

		ISC_LIST_APPEND(newname->list, newrdataset, link);
	}

	*newnamep = newname;

	return (ISC_R_SUCCESS);

 fail:
	dns_message_puttempname(msg, &newname);

	return (result);

}
