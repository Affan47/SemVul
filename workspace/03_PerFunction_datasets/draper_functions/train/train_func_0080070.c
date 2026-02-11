dmi_string(const struct dmi_header *dm, u8 s)
{
	const char *bp = dmi_string_nosave(dm, s);
	char *str;
	size_t len;

	if (bp == dmi_empty_string)
		return dmi_empty_string;

	len = strlen(bp) + 1;
	str = dmi_alloc(len);
	if (str != NULL)
		strcpy(str, bp);

	return str;
}
