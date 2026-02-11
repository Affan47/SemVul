numericvar_to_double(numeric *var, double *dp)
{
	char	   *tmp;
	double		val;
	char	   *endptr;
	numeric    *varcopy = PGTYPESnumeric_new();

	if (varcopy == NULL)
		return -1;

	if (PGTYPESnumeric_copy(var, varcopy) < 0)
	{
		PGTYPESnumeric_free(varcopy);
		return -1;
	}

	tmp = get_str_from_var(varcopy, varcopy->dscale);
	PGTYPESnumeric_free(varcopy);

	if (tmp == NULL)
		return -1;


	errno = 0;
	val = strtod(tmp, &endptr);
	if (errno == ERANGE)
	{
		free(tmp);
		if (val == 0)
			errno = PGTYPES_NUM_UNDERFLOW;
		else
			errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}


	if (*endptr != '\0')
	{

		free(tmp);
		errno = PGTYPES_NUM_BAD_NUMERIC;
		return -1;
	}
	free(tmp);
	*dp = val;
	return 0;
}
