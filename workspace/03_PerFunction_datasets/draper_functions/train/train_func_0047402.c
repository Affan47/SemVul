PGTYPESnumeric_to_asc(numeric *num, int dscale)
{
	numeric    *numcopy = PGTYPESnumeric_new();
	char	   *s;

	if (numcopy == NULL)
		return NULL;

	if (PGTYPESnumeric_copy(num, numcopy) < 0)
	{
		PGTYPESnumeric_free(numcopy);
		return NULL;
	}

	if (dscale < 0)
		dscale = num->dscale;


	s = get_str_from_var(numcopy, dscale);
	PGTYPESnumeric_free(numcopy);
	return (s);
}
