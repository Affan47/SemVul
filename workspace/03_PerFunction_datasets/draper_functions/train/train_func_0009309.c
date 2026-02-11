tomoyo_set_uint(unsigned int *i, const char *string,
			    const char *find)
{
	const char *cp = strstr(string, find);
	if (cp)
		sscanf(cp + strlen(find), "=%u", i);
}
