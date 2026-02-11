int44out(PG_FUNCTION_ARGS)
{
	int32	   *an_array = (int32 *) PG_GETARG_POINTER(0);
	char	   *result = (char *) palloc(16 * 4);

	int			i;
	char	   *walk;

	walk = result;
	for (i = 0; i < 4; i++)
	{
		pg_ltoa(an_array[i], walk);
		while (*++walk != '\0')
			;
		*walk++ = ' ';
	}
	*--walk = '\0';
	PG_RETURN_CSTRING(result);
}
