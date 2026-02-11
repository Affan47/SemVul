strtouint32(const char *s)
{
	char *end;
	uintmax_t n = strtoumax(s, &end, 10);
	if (*s == '\0' || (*end != '\n' && *end != '\0'))
		die("invalid offset: %s", s);
	return (uint32_t) n;
}
