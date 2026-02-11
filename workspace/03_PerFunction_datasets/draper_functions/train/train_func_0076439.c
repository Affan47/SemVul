regnext(regex_t *preg, int p )
{
	int offset;

	offset = NEXT(preg, p);

	if (offset == 0)
		return 0;

	if (OP(preg, p) == BACK)
		return(p-offset);
	else
		return(p+offset);
}
