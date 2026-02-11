nrv_alloc(CONST char *s, char **rve, int n)
{
	char *rv, *t;

	t = rv = rv_alloc(n);
	while((*t = *s++)) t++;
	if (rve)
		*rve = t;
	return rv;
	}
