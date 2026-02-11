gsf_msole_iconv_win_codepage (void)
{
	char *lang;

	if ((lang = getenv("WINDOWS_LANGUAGE")) == NULL) {
		char const *locale = setlocale (LC_CTYPE, NULL);
		if (locale != NULL) {
			char const *lang_sep = strchr (locale, '.');
			if (lang_sep)
				lang = g_strndup (locale, (unsigned)(lang_sep - locale));
			else
				lang = g_strdup (locale);
		}
	}

	if (lang != NULL) {
		guint lid = gsf_msole_lid_for_language (lang);
		g_free (lang);
		return gsf_msole_lid_to_codepage (lid);
	}
	return 1252;
}
