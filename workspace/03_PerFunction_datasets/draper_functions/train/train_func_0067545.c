blkid_rtrim_whitespace(unsigned char *str)
{
	size_t i = strlen((char *) str);

	while (i--) {
		if (!isspace(str[i]))
			break;
	}
	str[++i] = '\0';
	return i;
}
