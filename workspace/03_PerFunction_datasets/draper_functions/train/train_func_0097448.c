initctx1(isc_task_t *task, isc_event_t *event) {
	char gssid[512];
	char contextname[512];
	isc_result_t result;
	isc_buffer_t buf;
	dns_message_t *query;
	dns_request_t *request;
	int c;

	isc_event_free(&event);

	printf("Initctx - GSS name => ");
	c = scanf("%511s", gssid);
	if (c == EOF)
		return;

	snprintf(contextname, sizeof(contextname),
		 "gsstest.context.%d.", (int)time(NULL));

	printf("Initctx - context name we're using: %s\n", contextname);

	printf("Negotiating GSSAPI context: ");
	printf("%s", gssid);
	printf("\n");


	dns_fixedname_init(&servername);
	isc_buffer_init(&buf, contextname, strlen(contextname));
	isc_buffer_add(&buf, strlen(contextname));
	result = dns_name_fromtext(dns_fixedname_name(&servername), &buf,
				   dns_rootname, 0, NULL);
	CHECK("dns_name_fromtext", result);


	dns_fixedname_init(&gssname);
	isc_buffer_init(&buf, gssid, strlen(gssid));
	isc_buffer_add(&buf, strlen(gssid));
	result = dns_name_fromtext(dns_fixedname_name(&gssname), &buf,
				   dns_rootname, 0, NULL);
	CHECK("dns_name_fromtext", result);

	query = NULL;
	result = dns_message_create(mctx, DNS_MESSAGE_INTENTRENDER, &query);
	CHECK("dns_message_create", result);

	printf("Calling gss_init_sec_context()\n");
	gssctx = GSS_C_NO_CONTEXT;
	result = dns_tkey_buildgssquery(query, dns_fixedname_name(&servername),
					dns_fixedname_name(&gssname),
					NULL, 36000, &gssctx, ISC_TRUE,
					mctx, NULL);
	CHECK("dns_tkey_buildgssquery", result);

	printf("Sending context token to server\n");
	request = NULL;
	result = dns_request_create(requestmgr, query, &address, 0, NULL,
				    TIMEOUT, task, initctx2, query, &request);
	CHECK("dns_request_create", result);

	return;
 end:
	event = isc_event_allocate(mctx, (void *)1, 1, console, NULL,
				   sizeof(*event));
	isc_task_send(task, &event);return;
}
