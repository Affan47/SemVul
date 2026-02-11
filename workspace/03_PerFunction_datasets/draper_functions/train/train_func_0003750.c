snarf_locale_from_key (const char *key)
{
	const char *brace;
	char *locale, *p;

	brace = strchr (key, '[');
	if (brace == NULL)
		return NULL;

	locale = g_strdup (brace + 1);
	if (*locale == '\0') {
		g_free (locale);
		return NULL;
	}
	p = strchr (locale, ']');
	if (p == NULL) {
		g_free (locale);
		return NULL;
	}
	*p = '\0';
	return locale;
}
