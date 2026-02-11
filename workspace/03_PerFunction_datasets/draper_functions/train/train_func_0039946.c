rpz_rewrite_ip_rrsets(ns_client_t *client, dns_name_t *name,
		      dns_rdatatype_t qtype, dns_rpz_type_t rpz_type,
		      dns_rdataset_t **ip_rdatasetp, isc_boolean_t resuming)
{
	dns_rpz_st_t *st;
	dns_dbversion_t *ip_version;
	dns_db_t *ip_db;
	dns_rdataset_t *p_rdataset;
	isc_result_t result;

	st = client->query.rpz_st;
	ip_version = NULL;
	ip_db = NULL;
	p_rdataset = NULL;
	if ((st->state & DNS_RPZ_DONE_IPv4) == 0 &&
	    (qtype == dns_rdatatype_a ||
	     qtype == dns_rdatatype_any ||
	     rpz_type == DNS_RPZ_TYPE_NSIP)) {


		result = rpz_rewrite_ip_rrset(client, name, qtype,
					      rpz_type, dns_rdatatype_a,
					      &ip_db, ip_version, ip_rdatasetp,
					      &p_rdataset, resuming);
		if (result == ISC_R_SUCCESS)
			st->state |= DNS_RPZ_DONE_IPv4;
	} else {
		result = ISC_R_SUCCESS;
	}
	if (result == ISC_R_SUCCESS &&
	    (qtype == dns_rdatatype_aaaa ||
	     qtype == dns_rdatatype_any ||
	     rpz_type == DNS_RPZ_TYPE_NSIP)) {


		result = rpz_rewrite_ip_rrset(client, name,  qtype,
					      rpz_type, dns_rdatatype_aaaa,
					      &ip_db, ip_version, ip_rdatasetp,
					      &p_rdataset, resuming);
	}
	if (ip_db != NULL)
		dns_db_detach(&ip_db);
	query_putrdataset(client, &p_rdataset);
	return (result);
}
