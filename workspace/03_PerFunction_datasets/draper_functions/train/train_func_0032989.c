verify(dns_validator_t *val, dst_key_t *key, dns_rdata_t *rdata,
       isc_uint16_t keyid)
{
	isc_result_t result;
	dns_fixedname_t fixed;
	isc_boolean_t ignore = ISC_FALSE;
	dns_name_t *wild;

	val->attributes |= VALATTR_TRIEDVERIFY;
	dns_fixedname_init(&fixed);
	wild = dns_fixedname_name(&fixed);
 again:
	result = dns_dnssec_verify3(val->event->name, val->event->rdataset,
				    key, ignore, val->view->maxbits,
				    val->view->mctx, rdata, wild);
	if ((result == DNS_R_SIGEXPIRED || result == DNS_R_SIGFUTURE) &&
	    val->view->acceptexpired)
	{
		ignore = ISC_TRUE;
		goto again;
	}
	if (ignore && (result == ISC_R_SUCCESS || result == DNS_R_FROMWILDCARD))
		validator_log(val, ISC_LOG_INFO,
			      "accepted expired %sRRSIG (keyid=%u)",
			      (result == DNS_R_FROMWILDCARD) ?
			      "wildcard " : "", keyid);
	else if (result == DNS_R_SIGEXPIRED || result == DNS_R_SIGFUTURE)
		validator_log(val, ISC_LOG_INFO,
			      "verify failed due to bad signature (keyid=%u): "
			      "%s", keyid, isc_result_totext(result));
	else
		validator_log(val, ISC_LOG_DEBUG(3),
			      "verify rdataset (keyid=%u): %s",
			      keyid, isc_result_totext(result));
	if (result == DNS_R_FROMWILDCARD) {
		if (!dns_name_equal(val->event->name, wild)) {
			dns_name_t *closest;
			unsigned int labels;


			closest = dns_fixedname_name(&val->closest);
			dns_name_copy(wild, closest, NULL);
			labels = dns_name_countlabels(closest) - 1;
			dns_name_getlabelsequence(closest, 1, labels, closest);
			val->attributes |= VALATTR_NEEDNOQNAME;
		}
		result = ISC_R_SUCCESS;
	}
	return (result);
}
