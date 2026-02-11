get_parent_name(const TMTag *tag, filetype_id ft_id)
{
	const gchar *scope = tag->atts.entry.scope;
	const gchar *separator = symbols_get_context_separator(ft_id);
	const gchar *str, *ptr;

	if (!scope)
		return NULL;

	str = scope;

	while (1)
	{
		ptr = strstr(str, separator);
		if (ptr)
		{
			str = ptr + strlen(separator);
		}
		else
			break;
	}

	return NZV(str) ? str : NULL;
}
