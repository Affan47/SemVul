is_int_arg(char *arg)
{
	char *endptr;
	long val;

	if (arg[0] == '\0')
		return false;

	val = strtol(arg, &endptr, 10);

	if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		return false;

	if (errno != 0 && val == 0)
		return false;

	if (endptr[0] == '\0')
		return true;

	return false;
}
