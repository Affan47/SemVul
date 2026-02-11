_g_build_uri (const char *base, ...)
{
	va_list     args;
	const char *child;
	GString    *uri;

	uri = g_string_new (base);

	va_start (args, base);
	while ((child = va_arg (args, const char *)) != NULL) {
		if (! g_str_has_suffix (uri->str, "/") && ! g_str_has_prefix (child, "/"))
			g_string_append (uri, "/");
		g_string_append (uri, child);
	}
	va_end (args);

	return g_string_free (uri, FALSE);
}
