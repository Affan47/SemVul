url_get_host(dico_url_t url, char **str)
{
    char *s = *str;
    size_t len = strcspn(s, "/:");

    if (s[len] == ':') {
	char *q;
	unsigned long n = strtoul(s + len + 1, &q, 10);
	if ((*q && !strchr("/;:", *q)) || n > USHRT_MAX)
	    return 1;
	url->port = n;
	*str = q + strcspn(q, "/");
    } else
	*str = s + len;
    if (alloc_string_len(&url->host, s, len))
	return 1;
    if (**str) {
	++*str;
	return url_get_path(url, str);
    }
    return 0;
}
