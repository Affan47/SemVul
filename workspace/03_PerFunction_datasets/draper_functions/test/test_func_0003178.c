sa_strncpy_safe(char *dest, size_t len, const char *src, size_t src_len)
{
	char *dp = dest;
	const char *sp = src;

	while (len-- > 1 && src_len-- > 0 && *sp != '\0') {
		*dp++ = isprint(*sp) ? *sp : (isspace(*sp) ? ' ' : '.');
		sp++;
	}
	*dp = '\0';


	while (--dp >= dest && isspace(*dp))
		*dp = '\0';
	return dest;
}
