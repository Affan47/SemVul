Util_sscandouble(char const *s, double *dest)
{
	char *endptr;
	double result;

	result = strtod(s, &endptr);
	if (endptr[0] != '\0' || errno == ERANGE)
		return FALSE;
	*dest = result;
	return TRUE;

}
