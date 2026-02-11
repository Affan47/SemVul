STRING_add(char *str, const char *src, int len)
{
	int old_len;

	if (len <= 0 && src != NULL)
		len = strlen(src);

	if (len <= 0)
		return str;

	old_len = STRING_length(str);

	str = STRING_extend(str, old_len + len);
	if (src)
	{
		memcpy(&str[old_len], src, len);
		str[old_len + len] = 0;
	}

	return str;
}
