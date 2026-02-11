g_mime_charset_map_init (void)
{
	char *charset, *iconv_name, *locale;
	int i;

	if (iconv_charsets)
		return;

	iconv_charsets = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	for (i = 0; known_iconv_charsets[i].charset != NULL; i++) {
		charset = g_ascii_strdown (known_iconv_charsets[i].charset, -1);
		iconv_name = g_strdup (known_iconv_charsets[i].iconv_name);
		g_hash_table_insert (iconv_charsets, charset, iconv_name);
	}

#ifndef WIN32
#ifdef HAVE_CODESET
	if ((locale_charset = nl_langinfo (CODESET)) && locale_charset[0]) {
#ifdef __CYGWIN__


		if (strcmp (locale_charset, "US-ASCII") != 0) {

			locale_charset = g_ascii_strdown (locale_charset, -1);
		} else {

			locale_charset = NULL;
		}
#else
		locale_charset = g_ascii_strdown (locale_charset, -1);
#endif
	} else
		locale_charset = NULL;
#endif


	if (!(locale = getenv ("LC_ALL")) || !locale[0])
		if (!(locale = getenv ("LC_CTYPE")) || !locale[0])
			locale = getenv ("LANG");

	if (!locale || !locale[0] || !strcmp (locale, "C") || !strcmp (locale, "POSIX")) {


		locale_charset = NULL;
		locale_lang = NULL;
	} else {


		char *codeset, *p;

		if (!locale_charset) {
			codeset = strchr (locale, '.');
			if (codeset) {
				codeset++;


				p = codeset;
				while (*p && !strchr ("@;/", *p))
					p++;

				locale_charset = g_ascii_strdown (codeset, (size_t)(p - codeset));
			} else {

				locale_charset = NULL;
			}
		}

		locale_parse_lang (locale);
	}
#else
	locale_charset = g_strdup_printf ("cp%u", GetACP ());
#endif
}
