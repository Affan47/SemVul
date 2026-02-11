ext_strncpy(char *dst, const char *src, int len)
{
	int count = 0;
	int insquares = 0;

	while (*src && (count < len - 1)) {
		if (*src == '[') {
			insquares = 1;
		} else if (*src == ']') {
			insquares = 0;
		} else if (*src == ' ' && !insquares) {
			src++;
			continue;
		}
		*dst = *src;
		dst++;
		src++;
		count++;
	}
	*dst = '\0';

	return count;
}
