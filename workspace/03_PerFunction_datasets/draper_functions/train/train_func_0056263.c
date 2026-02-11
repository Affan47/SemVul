replace_whitespace(const char *str, char *to, size_t len)
{
	size_t i, j;


	len = strnlen(str, len);
	while (len && isspace(str[len-1]))
		len--;


	i = 0;
	while (isspace(str[i]) && (i < len))
		i++;

	j = 0;
	while (i < len) {

		if (isspace(str[i])) {
			while (isspace(str[i]))
				i++;
			to[j++] = '_';
		}
		to[j++] = str[i++];
	}
	to[j] = '\0';
	return 0;
}
