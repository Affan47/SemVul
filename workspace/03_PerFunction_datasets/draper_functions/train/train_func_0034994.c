regex_compile(const gchar *pattern)
{
	GError *error = NULL;
	GRegex *regex = g_regex_new(pattern, G_REGEX_CASELESS, 0, &error);

	if (!regex)
	{
		geany_debug("Failed to compile encoding regex (%s)", error->message);
		g_error_free(error);
	}
	return regex;
}
