email_address_extract (const guchar **cur,
                       gchar **out,
                       const guchar *linestart)
{
	const guchar *start, *end, *dot;
	gchar *addr;


	for (start = *cur; start - 1 >= linestart && is_addr_char (*(start - 1)); start--)
		;
	if (start == *cur)
		return NULL;
	if (start > linestart + 2 &&
	    start[-1] == ':' && start[0] == '/' && start[1] == '/')
		return NULL;


	for (end = *cur + 1, dot = NULL; is_domain_name_char (*end); end++) {
		if (*end == '.' && !dot)
			dot = end;
	}
	if (!dot)
		return NULL;


	while (is_trailing_garbage (*(end - 1)))
		end--;
	if (dot > end)
		return NULL;

	addr = g_strndup ((gchar *) start, end - start);
	*out -= *cur - start;
	*cur = end;

	return addr;
}
