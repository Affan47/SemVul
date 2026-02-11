printmessage(dig_query_t *query, dns_message_t *msg, isc_boolean_t headers) {
	char servtext[ISC_SOCKADDR_FORMATSIZE];


	query_error = 0;

	debug("printmessage()");

	isc_sockaddr_format(&query->sockaddr, servtext, sizeof(servtext));
	printf("Server:\t\t%s\n", query->userarg);
	printf("Address:\t%s\n", servtext);

	puts("");

	if (!short_form) {
		isc_boolean_t headers = ISC_TRUE;
		puts("------------");

		detailsection(query, msg, headers, DNS_SECTION_QUESTION);
		detailsection(query, msg, headers, DNS_SECTION_ANSWER);
		detailsection(query, msg, headers, DNS_SECTION_AUTHORITY);
		detailsection(query, msg, headers, DNS_SECTION_ADDITIONAL);
		puts("------------");
	}

	if (msg->rcode != 0) {
		char nametext[DNS_NAME_FORMATSIZE];
		dns_name_format(query->lookup->name,
				nametext, sizeof(nametext));
		printf("** server can't find %s: %s\n",
		       nametext, rcode_totext(msg->rcode));
		debug("returning with rcode == 0");


		print_error |= 1;
		return (ISC_R_SUCCESS);
	}

	if ((msg->flags & DNS_MESSAGEFLAG_AA) == 0)
		puts("Non-authoritative answer:");
	if (!ISC_LIST_EMPTY(msg->sections[DNS_SECTION_ANSWER]))
		printsection(query, msg, headers, DNS_SECTION_ANSWER);
	else
		printf("*** Can't find %s: No answer\n",
		       query->lookup->textname);

	if (((msg->flags & DNS_MESSAGEFLAG_AA) == 0) &&
	    (query->lookup->rdtype != dns_rdatatype_a)) {
		puts("\nAuthoritative answers can be found from:");
		printsection(query, msg, headers,
			     DNS_SECTION_AUTHORITY);
		printsection(query, msg, headers,
			     DNS_SECTION_ADDITIONAL);
	}
	return (ISC_R_SUCCESS);
}
