sylk_parse_value (SylkReader *state, const char *str)
{
	GnmValue *val;
	if ('\"' == *str) {
		size_t len;

		str++;
		len = strlen (str);
		if (len > 0 && str[len - 1] == '\"')
			len--;
		return value_new_string_nocopy (g_strndup (str, len));
	}

	val = format_match_simple (str);
	if (val)
		return val;

	return value_new_string (str);
}
