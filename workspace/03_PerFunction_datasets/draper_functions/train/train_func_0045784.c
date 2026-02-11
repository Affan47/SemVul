get_cookies(List *headers, const WSPMachine *sm)
{
	Octstr *header = NULL;
	Octstr *value = NULL;
	Cookie *cookie = NULL;
	long pos = 0;


	if (sm == NULL) {
		info (0, "No session machine for cookie retrieval");
		return 0;
	}

	for (pos = 0; pos < gwlist_len(headers); pos++) {
		header = gwlist_get(headers, pos);

		if (strncasecmp ("set-cookie", octstr_get_cstr (header),10) == 0) {
			debug ("wap.wsp.http", 0, "Caching cookie (%s)", octstr_get_cstr (header));

			if ((value = get_header_value (header)) == NULL) {
				error (0, "get_cookies: No value in (%s)", octstr_get_cstr(header));
				continue;
			}


			if ((cookie = parse_cookie(value)) != NULL) {


				if (have_cookie(sm->cookies, cookie) == 1) {
					debug("wap.wsp.http", 0, "parse_cookie: Cookie present");
					      cookie_destroy(cookie);
					continue;
				} else {
					add_cookie_to_cache(sm, cookie);
					debug("wap.wsp.http", 0, "get_cookies: Added (%s)",
						  octstr_get_cstr(cookie -> name));
				}
			}
		}
	}

	debug("wap.wsp.http", 0, "get_cookies: End");
	return 0;
}
