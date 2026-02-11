pg_regprefix(regex_t *re,
			 chr **string,
			 size_t *slength)
{
	struct guts *g;
	struct cnfa *cnfa;
	int			st;


	if (string == NULL || slength == NULL)
		return REG_INVARG;
	*string = NULL;
	*slength = 0;
	if (re == NULL || re->re_magic != REMAGIC)
		return REG_INVARG;
	if (re->re_csize != sizeof(chr))
		return REG_MIXED;


	pg_set_regex_collation(re->re_collation);


	g = (struct guts *) re->re_guts;
	if (g->info & REG_UIMPOSSIBLE)
		return REG_NOMATCH;


	assert(g->tree != NULL);
	cnfa = &g->tree->cnfa;


	*string = (chr *) MALLOC(cnfa->nstates * sizeof(chr));
	if (*string == NULL)
		return REG_ESPACE;


	st = findprefix(cnfa, &g->cmap, *string, slength);

	assert(*slength <= cnfa->nstates);


	if (st != REG_PREFIX && st != REG_EXACT)
	{
		FREE(*string);
		*string = NULL;
		*slength = 0;
	}

	return st;
}
