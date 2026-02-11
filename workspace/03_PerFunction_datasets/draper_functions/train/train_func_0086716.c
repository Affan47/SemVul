rpz_log_fail(ns_client_t *client, int level, dns_name_t *p_name,
	     dns_rpz_type_t rpz_type, const char *str, isc_result_t result)
{
	char qnamebuf[DNS_NAME_FORMATSIZE];
	char p_namebuf[DNS_NAME_FORMATSIZE];
	const char *failed;

	if (!isc_log_wouldlog(ns_g_lctx, level))
		return;


	if (level <= DNS_RPZ_DEBUG_LEVEL1)
		failed = "failed: ";
	else
		failed = ": ";
	dns_name_format(client->query.qname, qnamebuf, sizeof(qnamebuf));
	dns_name_format(p_name, p_namebuf, sizeof(p_namebuf));
	ns_client_log(client, NS_LOGCATEGORY_QUERY_EERRORS,
		      NS_LOGMODULE_QUERY, level,
		      "rpz %s rewrite %s via %s%s%s%s",
		      dns_rpz_type2str(rpz_type),
		      qnamebuf, p_namebuf,
		      str, failed, isc_result_totext(result));
}
