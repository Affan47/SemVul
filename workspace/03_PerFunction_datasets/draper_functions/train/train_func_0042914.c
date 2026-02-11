update_regex_flags (GRegexCompileFlags  flags,
		    const xmlChar      *option_name,
		    const xmlChar      *value)
{
	GRegexCompileFlags single_flag;
	gboolean set_flag;

	DEBUG (g_message ("setting the '%s' regex flag to %s", option_name, value));

	set_flag = str_to_bool (value);

	if (xmlStrcmp (BAD_CAST "case-sensitive", option_name) == 0)
	{
		single_flag = G_REGEX_CASELESS;
		set_flag = !set_flag;
	}
	else if (xmlStrcmp (BAD_CAST "extended", option_name) == 0)
	{
		single_flag = G_REGEX_EXTENDED;
	}
	else if (xmlStrcmp (BAD_CAST "dupnames", option_name) == 0)
	{
		single_flag = G_REGEX_DUPNAMES;
	}
	else
	{
		return flags;
	}

	if (set_flag)
		flags |= single_flag;
	else
		flags &= ~single_flag;

	return flags;
}
