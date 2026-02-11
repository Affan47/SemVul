dsynonym_init(PG_FUNCTION_ARGS)
{
	List	   *dictoptions = (List *) PG_GETARG_POINTER(0);
	DictSyn    *d;
	ListCell   *l;
	char	   *filename = NULL;
	bool		case_sensitive = false;
	tsearch_readline_state trst;
	char	   *starti,
			   *starto,
			   *end = NULL;
	int			cur = 0;
	char	   *line = NULL;

	foreach(l, dictoptions)
	{
		DefElem    *defel = (DefElem *) lfirst(l);

		if (pg_strcasecmp("Synonyms", defel->defname) == 0)
			filename = defGetString(defel);
		else if (pg_strcasecmp("CaseSensitive", defel->defname) == 0)
			case_sensitive = defGetBoolean(defel);
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unrecognized synonym parameter: \"%s\"",
							defel->defname)));
	}

	if (!filename)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("missing Synonyms parameter")));

	filename = get_tsearch_config_filename(filename, "syn");

	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open synonym file \"%s\": %m",
						filename)));

	d = (DictSyn *) palloc0(sizeof(DictSyn));

	while ((line = tsearch_readline(&trst)) != NULL)
	{
		starti = findwrd(line, &end);
		if (!starti)
		{

			goto skipline;
		}
		if (*end == '\0')
		{

			goto skipline;
		}
		*end = '\0';

		starto = findwrd(end + 1, &end);
		if (!starto)
		{

			goto skipline;
		}
		*end = '\0';


		if (cur >= d->len)
		{
			if (d->len == 0)
			{
				d->len = 64;
				d->syn = (Syn *) palloc(sizeof(Syn) * d->len);
			}
			else
			{
				d->len *= 2;
				d->syn = (Syn *) repalloc(d->syn, sizeof(Syn) * d->len);
			}
		}

		if (case_sensitive)
		{
			d->syn[cur].in = pstrdup(starti);
			d->syn[cur].out = pstrdup(starto);
		}
		else
		{
			d->syn[cur].in = lowerstr(starti);
			d->syn[cur].out = lowerstr(starto);
		}

		cur++;

skipline:
		pfree(line);
	}

	tsearch_readline_end(&trst);

	d->len = cur;
	qsort(d->syn, d->len, sizeof(Syn), compareSyn);

	d->case_sensitive = case_sensitive;

	PG_RETURN_POINTER(d);
}
