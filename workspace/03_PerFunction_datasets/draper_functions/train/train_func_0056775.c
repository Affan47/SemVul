RCS_parsercsfile_i (FILE *fp, const char *rcsfile)
{
    RCSNode *rdata;
    struct rcsbuffer rcsbuf;
    char *key, *value;


    rdata = xmalloc (sizeof (RCSNode));
    memset (rdata, 0, sizeof (RCSNode));
    rdata->refcount = 1;
    rdata->path = xstrdup (rcsfile);
    rdata->print_path = xstrdup (primary_root_inverse_translate (rcsfile));


    rcsbuf_open (&rcsbuf, fp, rcsfile, 0);

    if (! rcsbuf_getkey (&rcsbuf, &key, &value))
	goto l_error;
    if (STREQ (key, RCSDESC))
	goto l_error;

    if (STREQ (RCSHEAD, key) && value != NULL)
	rdata->head = rcsbuf_valcopy (&rcsbuf, value, 0, NULL);

    if (! rcsbuf_getkey (&rcsbuf, &key, &value))
	goto l_error;
    if (STREQ (key, RCSDESC))
	goto l_error;

    if (STREQ (RCSBRANCH, key) && value != NULL)
    {
	char *cp;

	rdata->branch = rcsbuf_valcopy (&rcsbuf, value, 0, NULL);
	if ((numdots (rdata->branch) & 1) != 0)
	{

	    cp = strrchr (rdata->branch, '.');
	    *cp = '\0';
	}
    }


    while (1)
    {
	char *cp;

	if (STREQ (RCSEXPAND, key))
	{
	    rdata->expand = rcsbuf_valcopy (&rcsbuf, value, 0, NULL);
	    break;
	}

	for (cp = key;
	     (isdigit ((unsigned char)*cp) || *cp == '.') && *cp != '\0';
	     cp++)
	     ;
	if (*cp == '\0')
	    break;

	if (STREQ (RCSDESC, key))
	    break;

	if (! rcsbuf_getkey (&rcsbuf, &key, &value))
	    break;
    }

    rdata->flags |= PARTIAL;

    rcsbuf_cache (rdata, &rcsbuf);

    return rdata;

l_error:
    error (0, 0, "`%s' does not appear to be a valid rcs file",
	   rcsfile);
    rcsbuf_close (&rcsbuf);
    freercsnode (&rdata);
    fclose (fp);
    return NULL;
}
