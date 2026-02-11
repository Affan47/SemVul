convnames(const char *pp)
{
	struct rfc822t *t;
	struct rfc822a *a;
	int al;
	char *q, *p=NULL;

	t=rfc822t_alloc_new(pp ? pp:"", NULL, NULL);
	if (!t)
	{
		perror("malloc");
		exit(1);
	}
	a=rfc822a_alloc(t);
	if (!a)
	{
		perror("malloc");
		exit(1);
	}

	al=1;

	if (rfc822_display_namelist(a, unicode_default_chset(),
				    cnt_names, &al) == 0)
	{
		q=p=courier_malloc(al+1);

		if (rfc822_display_namelist(a, unicode_default_chset(),
					    save_names, &q) == 0)
		{
			if (q - p >= 2 && q[-1] == ' ' && q[-2] == ',')

				q -= 2;

			*q=0;
		}
	}
	rfc822a_free(a);
	rfc822t_free(t);
	return (p);
}
