lb_field_value_buf(const char *p)
{
	const char *q;
	char *r;

	while (p && *p && *p != '\t')
		if ( *p++ == '=')
			break;

	if (!p)
		return (strdup(""));

	q=strchr(p, '\t');
	if (!q)
		return (strdup(p));

	r=malloc(q-p+1);

	if (!r)
		return (NULL);

	memcpy(r, p, q-p);
	r[q-p]=0;
	return (r);
}
