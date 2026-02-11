PGTYPESnumeric_to_int(numeric *nv, int *ip)
{
	long		l;
	int			i;

	if ((i = PGTYPESnumeric_to_long(nv, &l)) != 0)
		return i;

	if (l < -INT_MAX || l > INT_MAX)
	{
		errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}

	*ip = (int) l;
	return 0;
}
