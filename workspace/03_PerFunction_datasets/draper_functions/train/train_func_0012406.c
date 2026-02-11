checkmx(dns_zone_t *zone, dns_name_t *name, dns_name_t *owner) {
#ifdef USE_GETADDRINFO
	struct addrinfo hints, *ai, *cur;
	char namebuf[DNS_NAME_FORMATSIZE + 1];
	char ownerbuf[DNS_NAME_FORMATSIZE];
	int result;
	int level = ISC_LOG_ERROR;
	isc_boolean_t answer = ISC_TRUE;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	dns_name_format(name, namebuf, sizeof(namebuf) - 1);


	if (dns_name_countlabels(name) > 1U)
		strcat(namebuf, ".");
	dns_name_format(owner, ownerbuf, sizeof(ownerbuf));

	result = getaddrinfo(namebuf, NULL, &hints, &ai);
	dns_name_format(name, namebuf, sizeof(namebuf) - 1);
	switch (result) {
	case 0:


		cur = ai;
		while (cur != NULL && cur->ai_canonname == NULL &&
		       cur->ai_next != NULL)
			cur = cur->ai_next;
		if (cur != NULL && cur->ai_canonname != NULL &&
		    strcasecmp(cur->ai_canonname, namebuf) != 0) {
			if ((zone_options & DNS_ZONEOPT_WARNMXCNAME) != 0)
				level = ISC_LOG_WARNING;
			if ((zone_options & DNS_ZONEOPT_IGNOREMXCNAME) == 0) {
				if (!logged(namebuf, ERR_IS_MXCNAME)) {
					dns_zone_log(zone, level,
						     "%s/MX '%s' (out of zone)"
						     " is a CNAME '%s' "
						     "(illegal)",
						     ownerbuf, namebuf,
						     cur->ai_canonname);
					add(namebuf, ERR_IS_MXCNAME);
				}
				if (level == ISC_LOG_ERROR)
					answer = ISC_FALSE;
			}
		}
		freeaddrinfo(ai);
		return (answer);

	case EAI_NONAME:
#if defined(EAI_NODATA) && (EAI_NODATA != EAI_NONAME)
	case EAI_NODATA:
#endif
		if (!logged(namebuf, ERR_NO_ADDRESSES)) {
			dns_zone_log(zone, ISC_LOG_ERROR,
				     "%s/MX '%s' (out of zone) "
				     "has no addresses records (A or AAAA)",
				     ownerbuf, namebuf);
			add(namebuf, ERR_NO_ADDRESSES);
		}

		return (ISC_TRUE);

	default:
		if (!logged(namebuf, ERR_LOOKUP_FAILURE)) {
			dns_zone_log(zone, ISC_LOG_WARNING,
			     "getaddrinfo(%s) failed: %s",
			     namebuf, gai_strerror(result));
			add(namebuf, ERR_LOOKUP_FAILURE);
		}
		return (ISC_TRUE);
	}
#else
	return (ISC_TRUE);
#endif
}
