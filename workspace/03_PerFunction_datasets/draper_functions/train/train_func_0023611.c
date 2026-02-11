strtok_raw(char *output, char *src, char *delimit, int keep)
{
	while (*src && strchr(delimit, *src) == NULL)
		*output++ = *src++;

	*output = 0;

	if (keep)
		return src;
	else
		return *src ? src+1 : src;
}
