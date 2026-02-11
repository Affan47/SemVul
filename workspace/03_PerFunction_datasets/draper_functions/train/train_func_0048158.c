url_absolute_within(const char *base, const char *relative)
{
	char *dbase = NULL;

	g_assert(url_is_absolute(base));

	if (url_is_absolute(relative))
		return deconstify_char(relative);

	if (is_strprefix(relative, "//"))

		return h_strconcat("http:", relative, NULL);

	if (is_strprefix(relative, "#")) {
		char *p;

		if (NULL == (p = strchr(base, '#'))) {
			return h_strconcat(base, relative, NULL);
		} else {

			dbase = h_strdup(base);
			p = dbase + (p - base);
			g_assert(*p == '#');
			*p = '\0';
			goto concatenate;
		}
	}

	if (is_strprefix(relative, "/")) {
		char *p;

		dbase = h_strdup(base);
		p = is_strprefix(dbase, http_prefix);
		g_assert(p != NULL);
		p = strchr(p, '/');

		if (NULL == p) {

			hfree(dbase);
			return h_strconcat(base, relative, NULL);
		} else {

			*p = '\0';
			goto concatenate;
		}
	} else {
		char *p;


		dbase = h_strdup(base);
		p = strrchr(dbase, '/');
		g_assert(p != NULL);
		*(++p) = '\0';


	}

concatenate:
	{
		char *result;

		g_assert(dbase != NULL);

		result = h_strconcat(dbase, relative, NULL);
		hfree(dbase);
		return result;
	}
}
