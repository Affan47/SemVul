chkbadlist(const char *pp, struct bofh_list *b)
{
	char *p=courier_malloc(strlen(pp)+1);
	const char *d;
	int l, ll;

	strcpy(p, pp);
	address_lower(p);

	d=strrchr(p, '@');
	l=d ? strlen(d):0;

	for (; b; b=b->next)
	{
		if ((d && strcmp(d, b->name) == 0)
		    ||
		    chkusersubdom(p, d, b->name)
		    ||
		    strcmp(p, b->name) == 0
		    || (d && strncmp(b->name, "@.", 2) == 0
			&& (ll=strlen(b->name+1)) < l
			&& strcmp(d+l - ll, b->name+1) == 0))
		{
			free(p);
			return (1);
		}
	}
	free(p);
	return (0);
}
