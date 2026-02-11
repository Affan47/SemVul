rfc822_coresubj_nouc(const char *s, int *hasrefwd)
{
	char *q=strdup(s);
	int dummy;

	if (!hasrefwd)
		hasrefwd= &dummy;

	*hasrefwd=0;
	if (!q)	return (0);

	stripsubj(q, hasrefwd, 0);
	return (q);
}
