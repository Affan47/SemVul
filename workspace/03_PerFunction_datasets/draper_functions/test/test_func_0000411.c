checkkey(dns_validator_t *val, dns_rdata_t *keyrdata, isc_uint16_t keyid,
	 dns_secalg_t algorithm)
{
	dns_rdata_rrsig_t sig;
	dst_key_t *dstkey = NULL;
	isc_result_t result;

	for (result = dns_rdataset_first(val->event->sigrdataset);
	     result == ISC_R_SUCCESS;
	     result = dns_rdataset_next(val->event->sigrdataset))
	{
		dns_rdata_t rdata = DNS_RDATA_INIT;

		dns_rdataset_current(val->event->sigrdataset, &rdata);
		result = dns_rdata_tostruct(&rdata, &sig, NULL);
		RUNTIME_CHECK(result == ISC_R_SUCCESS);
		if (keyid != sig.keyid || algorithm != sig.algorithm)
			continue;
		if (dstkey == NULL) {
			result = dns_dnssec_keyfromrdata(val->event->name,
							 keyrdata,
							 val->view->mctx,
							 &dstkey);
			if (result != ISC_R_SUCCESS)


				continue;
		}
		result = verify(val, dstkey, &rdata, sig.keyid);
		if (result == ISC_R_SUCCESS)
			break;
	}
	if (dstkey != NULL)
		dst_key_free(&dstkey);
	return (result);
}
