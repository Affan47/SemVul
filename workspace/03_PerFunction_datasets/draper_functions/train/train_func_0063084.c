upnp_service_parse_type(const char *text,
	enum upnp_service_type *type, unsigned *version)
{
	char *dtext = NULL;
	char *p;
	bool ok = FALSE;


	p = strrchr(text, ':');
	if (p != NULL) {
		uint32 v;
		int error;

		v = parse_uint32(p + 1, NULL, 10, &error);
		if (error)
			goto done;

		*version = v;
	} else {
		goto done;
	}


	dtext = h_strdup(text);
	p = dtext + (p - text);
	g_assert(':' == *p);
	*p = '\0';


	p = is_strprefix(dtext, "urn:");
	if (NULL == p)
		goto done;


	*type = vxml_token_lookup(p, upnp_services, G_N_ELEMENTS(upnp_services));
	ok = TRUE;


done:
	HFREE_NULL(dtext);
	return ok;
}
