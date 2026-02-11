goodsig(dns_name_t *origin, dns_rdata_t *sigrdata, dns_name_t *name,
	dns_rdataset_t *keyrdataset, dns_rdataset_t *rdataset, isc_mem_t *mctx)
{
	dns_rdata_dnskey_t key;
	dns_rdata_rrsig_t sig;
	dst_key_t *dstkey = NULL;
	isc_result_t result;

	result = dns_rdata_tostruct(sigrdata, &sig, NULL);
	check_result(result, "dns_rdata_tostruct()");

	for (result = dns_rdataset_first(keyrdataset);
	     result == ISC_R_SUCCESS;
	     result = dns_rdataset_next(keyrdataset)) {
		dns_rdata_t rdata = DNS_RDATA_INIT;
		dns_rdataset_current(keyrdataset, &rdata);
		result = dns_rdata_tostruct(&rdata, &key, NULL);
		check_result(result, "dns_rdata_tostruct()");
		result = dns_dnssec_keyfromrdata(origin, &rdata, mctx,
						 &dstkey);
		if (result != ISC_R_SUCCESS)
			return (ISC_FALSE);
		if (sig.algorithm != key.algorithm ||
		    sig.keyid != dst_key_id(dstkey) ||
		    !dns_name_equal(&sig.signer, origin)) {
			dst_key_free(&dstkey);
			continue;
		}
		result = dns_dnssec_verify(name, rdataset, dstkey, ISC_FALSE,
					   mctx, sigrdata);
		dst_key_free(&dstkey);
		if (result == ISC_R_SUCCESS)
			return(ISC_TRUE);
	}
	return (ISC_FALSE);
}
