mime_getboundary(char *h)
{
	char *p, *q;
	size_t sz;

	if ((p = mime_getparam("boundary", h)) == NULL)
		return NULL;
	sz = strlen(p);
	q = salloc(sz + 3);
	memcpy(q, "--", 2);
	memcpy(q + 2, p, sz);
	*(q + sz + 2) = '\0';
	return q;
}
