float8in(PG_FUNCTION_ARGS)
{
	char	   *num = PG_GETARG_CSTRING(0);
	char	   *orig_num;
	double		val;
	char	   *endptr;


	orig_num = num;


	if (*num == '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type double precision: \"%s\"",
					orig_num)));


	while (*num != '\0' && isspace((unsigned char) *num))
		num++;

	errno = 0;
	val = strtod(num, &endptr);


	if (endptr == num || errno != 0)
	{


		if (pg_strncasecmp(num, "NaN", 3) == 0)
		{
			val = get_float8_nan();
			endptr = num + 3;
		}
		else if (pg_strncasecmp(num, "Infinity", 8) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 8;
		}
		else if (pg_strncasecmp(num, "-Infinity", 9) == 0)
		{
			val = -get_float8_infinity();
			endptr = num + 9;
		}
		else if (errno == ERANGE)
			ereport(ERROR,
					(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				   errmsg("\"%s\" is out of range for type double precision",
						  orig_num)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type double precision: \"%s\"",
					orig_num)));
	}
#ifdef HAVE_BUGGY_SOLARIS_STRTOD
	else
	{


		if (endptr != num && endptr[-1] == '\0')
			endptr--;
	}
#endif

#ifdef HAVE_BUGGY_IRIX_STRTOD


	if (isinf(val))
	{
		if (pg_strncasecmp(num, "Infinity", 8) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 8;
		}
		else if (pg_strncasecmp(num, "-Infinity", 9) == 0)
		{
			val = -get_float8_infinity();
			endptr = num + 9;
		}
		else if (pg_strncasecmp(num, "-inf", 4) == 0)
		{
			val = -get_float8_infinity();
			endptr = num + 4;
		}
	}
#endif


	while (*endptr != '\0' && isspace((unsigned char) *endptr))
		endptr++;


	if (*endptr != '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type double precision: \"%s\"",
					orig_num)));

	if (!isinf(val))
		CheckFloat8Val(val);

	PG_RETURN_FLOAT8(val);
}
