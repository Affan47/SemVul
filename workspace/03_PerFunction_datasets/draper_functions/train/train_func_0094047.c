seekto(const char *string, int n)
{
	const char *p = string;
	while (n--) {
		p = strchr(p, ' ');
		if (p == NULL)
			return NULL;
		p++;
	}
	return p;
}
