check_filteraaaa(cfg_aclconfctx_t *actx, const cfg_obj_t *voptions,
		 const char *viewname, const cfg_obj_t *config,
		 isc_log_t *logctx, isc_mem_t *mctx)
{
	const cfg_obj_t *options, *aclobj, *obj = NULL;
	dns_acl_t *acl = NULL;
	isc_result_t result = ISC_R_SUCCESS, tresult;
	dns_v4_aaaa_t filter;
	const char *forview = " for view ";

	if (voptions != NULL)
		cfg_map_get(voptions, "filter-aaaa-on-v4", &obj);
	if (obj == NULL && config != NULL) {
		options = NULL;
		cfg_map_get(config, "options", &options);
		if (options != NULL)
			cfg_map_get(options, "filter-aaaa-on-v4", &obj);
	}

	if (obj == NULL)
		filter = dns_v4_aaaa_ok;
	else if (cfg_obj_isboolean(obj))
		filter = cfg_obj_asboolean(obj) ? dns_v4_aaaa_filter :
						  dns_v4_aaaa_ok;
	else
		filter = dns_v4_aaaa_break_dnssec;

	if (viewname == NULL) {
		viewname = "";
		forview = "";
	}

	aclobj = options = NULL;
	acl = NULL;

	if (voptions != NULL)
		cfg_map_get(voptions, "filter-aaaa", &aclobj);
	if (config != NULL && aclobj == NULL) {
		options = NULL;
		cfg_map_get(config, "options", &options);
		if (options != NULL)
			cfg_map_get(options, "filter-aaaa", &aclobj);
	}
	if (aclobj == NULL)
		return (result);

	tresult = cfg_acl_fromconfig(aclobj, config, logctx,
				    actx, mctx, 0, &acl);

	if (tresult != ISC_R_SUCCESS) {
		result = tresult;
	} else if (filter != dns_v4_aaaa_ok && dns_acl_isnone(acl)) {
		cfg_obj_log(aclobj, logctx, ISC_LOG_WARNING,
			    "both \"filter-aaaa-on-v4 %s;\" and "
			    "\"filter-aaaa\" is 'none;'%s%s",
			    filter == dns_v4_aaaa_break_dnssec ?
			    "break-dnssec" : "yes", forview, viewname);
		result = ISC_R_FAILURE;
	} else if (filter == dns_v4_aaaa_ok && !dns_acl_isnone(acl)) {
		cfg_obj_log(aclobj, logctx, ISC_LOG_WARNING,
			    "both \"filter-aaaa-on-v4 no;\" and "
			    "\"filter-aaaa\" is set%s%s", forview, viewname);
		result = ISC_R_FAILURE;
	}

	if (acl != NULL)
		dns_acl_detach(&acl);

	return (result);
}
