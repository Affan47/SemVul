get_filename_charsets(const char *locale)
{
	const char *s, *next;
	bool has_locale = FALSE, has_utf8 = FALSE;
	GSList *sl = NULL;

	g_assert(locale);

	for (s = getenv("G_FILENAME_ENCODING"); s && '\0' != *s; s = next) {
		const char *ep;


		while (',' == *s || is_ascii_blank(*s))
			++s;

		next = strchr(s, ',');
		ep = next ? next : strchr(s, '\0');


		while (ep != s && is_ascii_blank(*(ep - 1)))
			--ep;

		if (ep != s) {
			const char *cs;

			if (is_strcaseprefix(s, "@locale") == ep) {
				cs = locale;
			} else {
				char *q = h_strndup(s, ep - s);
				cs = get_iconv_charset_alias(q);
				HFREE_NULL(q);
			}


			if (cs && 0 == strcmp(cs, "UTF-8")) {
				if (has_utf8)
					cs = NULL;
				has_utf8 = TRUE;
			}
			if (cs && 0 == strcmp(cs, locale)) {
				if (has_locale)
					cs = NULL;
				has_locale = TRUE;
			}

			if (cs)
				sl = g_slist_prepend(sl, conv_to_utf8_new(cs));
		}
	}


	if (!has_utf8)
		sl = g_slist_prepend(sl, conv_to_utf8_new("UTF-8"));


	if (!has_locale && 0 != strcmp("UTF-8", locale))
		sl = g_slist_prepend(sl, conv_to_utf8_new(locale));

	return g_slist_reverse(sl);
}
