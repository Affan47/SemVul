isns_assign_string(char **var, const char *val)
{
	char	*s = NULL;

	if (val && !(s = isns_strdup(val)))
		errx(1, "out of memory");

	if (*var)
		isns_free(*var);
	*var = s;
}
