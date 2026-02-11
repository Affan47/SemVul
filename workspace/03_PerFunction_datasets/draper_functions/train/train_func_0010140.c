SPF_server_set_localpolicy(SPF_server_t *sp, const char *policy,
				int use_default_whitelist,
				SPF_response_t **spf_responsep)
{
	SPF_record_t	*spf_record = NULL;
	SPF_errcode_t	 err;
	char			*record;
	size_t			 len;

	SPF_ASSERT_NOTNULL(policy);


	if (! *spf_responsep) {
		*spf_responsep = SPF_response_new(NULL);
		if (! *spf_responsep)
			return SPF_E_NO_MEMORY;
	}

	len = sizeof(SPF_VER_STR) + strlen(policy) + 20;
	if (use_default_whitelist)
		len += sizeof(SPF_DEFAULT_WHITELIST);
	record = malloc(len);
	if (! record)
		return SPF_E_NO_MEMORY;
	if (use_default_whitelist)
		snprintf(record, len, "%s %s %s",
						SPF_VER_STR, policy, SPF_DEFAULT_WHITELIST);
	else
		snprintf(record, len, "%s %s", SPF_VER_STR, policy);

	err = SPF_record_compile(sp, *spf_responsep, &spf_record, record);
	if (err == SPF_E_SUCCESS) {
		if (sp->local_policy)
			SPF_record_free(sp->local_policy);
		sp->local_policy = spf_record;
	}
	else {
		SPF_response_add_error(*spf_responsep, err,
				"Failed to compile local policy '%s'", policy);
		if (spf_record)
			SPF_record_free(spf_record);
	}

	free(record);

	return err;
}
