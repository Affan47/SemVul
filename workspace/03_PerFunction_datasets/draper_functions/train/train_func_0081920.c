ns_server_validation(ns_server_t *server, char *args, isc_buffer_t *text) {
	char *ptr, *viewname;
	dns_view_t *view;
	isc_boolean_t changed = ISC_FALSE;
	isc_result_t result;
	isc_boolean_t enable = ISC_TRUE, set = ISC_TRUE, first = ISC_TRUE;


	ptr = next_token(&args, " \t");
	if (ptr == NULL)
		return (ISC_R_UNEXPECTEDEND);


	ptr = next_token(&args, " \t");
	if (ptr == NULL)
		return (ISC_R_UNEXPECTEDEND);

	if (!strcasecmp(ptr, "on") || !strcasecmp(ptr, "yes") ||
	    !strcasecmp(ptr, "enable") || !strcasecmp(ptr, "true"))
		enable = ISC_TRUE;
	else if (!strcasecmp(ptr, "off") || !strcasecmp(ptr, "no") ||
		 !strcasecmp(ptr, "disable") || !strcasecmp(ptr, "false"))
		enable = ISC_FALSE;
	else if (!strcasecmp(ptr, "check"))
		set = ISC_FALSE;
	else
		return (DNS_R_SYNTAX);


	viewname = next_token(&args, " \t");

	result = isc_task_beginexclusive(server->task);
	RUNTIME_CHECK(result == ISC_R_SUCCESS);
	for (view = ISC_LIST_HEAD(server->viewlist);
	     view != NULL;
	     view = ISC_LIST_NEXT(view, link))
	{
		if (viewname != NULL && strcasecmp(viewname, view->name) != 0)
			continue;
		result = dns_view_flushcache(view);
		if (result != ISC_R_SUCCESS)
			goto cleanup;

		if (set) {
			view->enablevalidation = enable;
			changed = ISC_TRUE;
		} else {
			if (!first)
				CHECK(putstr(text, "\n"));
			CHECK(putstr(text, "DNSSEC validation is "));
			CHECK(putstr(text, view->enablevalidation
				       ? "enabled" : "disabled"));
			CHECK(putstr(text, " (view "));
			CHECK(putstr(text, view->name));
			CHECK(putstr(text, ")"));
			CHECK(putnull(text));
			first = ISC_FALSE;
		}
	}

	if (!set)
		result = ISC_R_SUCCESS;
	else if (changed)
		result = ISC_R_SUCCESS;
	else
		result = ISC_R_FAILURE;
 cleanup:
	isc_task_endexclusive(server->task);
	return (result);
}
