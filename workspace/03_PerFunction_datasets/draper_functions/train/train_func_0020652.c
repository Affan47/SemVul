anytime_typmodin(bool istz, ArrayType *ta)
{
	int32		typmod;
	int32	   *tl;
	int			n;

	tl = ArrayGetIntegerTypmods(ta, &n);


	if (n != 1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid type modifier")));

	if (*tl < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("TIME(%d)%s precision must not be negative",
						*tl, (istz ? " WITH TIME ZONE" : ""))));
	if (*tl > MAX_TIME_PRECISION)
	{
		ereport(WARNING,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("TIME(%d)%s precision reduced to maximum allowed, %d",
						*tl, (istz ? " WITH TIME ZONE" : ""),
						MAX_TIME_PRECISION)));
		typmod = MAX_TIME_PRECISION;
	}
	else
		typmod = *tl;

	return typmod;
}
