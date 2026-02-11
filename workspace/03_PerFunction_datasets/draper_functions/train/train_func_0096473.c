maildir_search_start_unicode(struct maildir_searchengine *sei,
				 const unicode_char *s)
{
	unsigned i, j, *r;

	size_t n;

	for (n=0; s[n]; ++n)
		;
	++n;

	if (sei->string)
		free(sei->string);

	sei->string=malloc(n * sizeof(*s));
	if (!sei->string)
		return (-1);
	sei->string_l=n-1;

	memcpy(sei->string, s, n * sizeof(*s));

	if (sei->r)
		free(sei->r);

	sei->i=0;
	if ((sei->r=r=(unsigned *)malloc(sizeof(unsigned)*n)) == 0)
		return (-1);

	for (i=0; s[i]; i++)
		r[i]=0;

	for (i=0; s[i]; i++)
		for (j=0; s[i+j]; j++)
			if (s[j] != s[i+j])
			{
				if (r[i+j] < j)
					r[i+j]=j;
				break;
			}

	maildir_search_reset(sei);
	return (0);
}
