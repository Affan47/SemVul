doenva(void (*writefunc)(const char *, size_t), char *s)
{
struct rfc822t *t;
struct rfc822a *a;
int	i;
char	*q, *r;

	if (!s)
	{
		(*writefunc)("NIL", 3);
		return;
	}

	t=rfc822t_alloc_new(s, 0, 0);
	if (!t)
	{
		perror("malloc");
		exit(0);
	}
	a=rfc822a_alloc(t);
	if (!a)
	{
		perror("malloc");
		exit(1);
	}

	if (a->naddrs == 0)
	{
		rfc822a_free(a);
		rfc822t_free(t);
		free(s);
		(*writefunc)("NIL", 3);
		return;
	}

	(*writefunc)("(", 1);
	for (i=0; i<a->naddrs; i++)
	{
		(*writefunc)("(", 1);

		q=rfc822_display_name_tobuf(a, i, NULL);

		if (!q)
		{
			perror("malloc");
			exit(1);
		}
		if (a->addrs[i].tokens == 0)
		{
			if (strcmp(q, ";") == 0)
			{
				(*writefunc)("NIL NIL NIL NIL)", 16);
				free(q);
				continue;
			}
			r=strrchr(q, ':');
			if (r && r[1] == 0)	*r=0;

			(*writefunc)("NIL NIL \"", 9);
			msgappends(writefunc, q, strlen(q));
			(*writefunc)("\" NIL)", 6);
			free(q);
			continue;
		}

		if (a->addrs[i].name == 0)
			*q=0;


		doenvs(writefunc, q);
		(*writefunc)(" NIL \"", 6);
		q=rfc822_gettok(a->addrs[i].tokens);
		if (!q)
		{
			perror("malloc");
			exit(1);
		}
		r=strrchr(q, '@');
		if (r)	*r++=0;
		msgappends(writefunc, q, strlen(q));
		(*writefunc)("\" \"", 3);
		if (r)
			msgappends(writefunc, r, strlen(r));
		(*writefunc)("\")", 2);
		free(q);
	}
	(*writefunc)(")", 1);
	rfc822a_free(a);
	rfc822t_free(t);
	free(s);
}
