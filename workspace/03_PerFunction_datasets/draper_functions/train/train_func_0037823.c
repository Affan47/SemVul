log_parse_revlist (const char *argstring)
{
    char *orig_copy, *copy;
    struct option_revlist *ret, **pr;


    if (argstring == NULL)
	argstring = "";

    ret = NULL;
    pr = &ret;


    orig_copy = copy = xstrdup (argstring);
    while (copy != NULL)
    {
	char *comma;
	struct option_revlist *r;

	comma = strchr (copy, ',');
	if (comma != NULL)
	    *comma++ = '\0';

	r = xmalloc (sizeof *r);
	r->next = NULL;
	r->first = copy;
	r->branchhead = 0;
	r->last = strchr (copy, ':');
	if (r->last != NULL)
	{
	    *r->last++ = '\0';
	    r->inclusive = (*r->last != ':');
	    if (!r->inclusive)
		r->last++;
	}
	else
	{
	    r->last = r->first;
	    r->inclusive = 1;
	    if (r->first[0] != '\0' && r->first[strlen (r->first) - 1] == '.')
	    {
		r->branchhead = 1;
		r->first[strlen (r->first) - 1] = '\0';
	    }
	}

	if (*r->first == '\0')
	    r->first = NULL;
	if (*r->last == '\0')
	    r->last = NULL;

	if (r->first != NULL)
	    r->first = xstrdup (r->first);
	if (r->last != NULL)
	    r->last = xstrdup (r->last);

	*pr = r;
	pr = &r->next;

	copy = comma;
    }

    free (orig_copy);
    return ret;
}
