bb_strtoll(const char *arg, char **endp, int base)
{
	unsigned long long v;
	char *endptr;


	char first = (arg[0] != '-' ? arg[0] : arg[1]);
	if (!isalnum(first)) return ret_ERANGE();

	errno = 0;
	v = strtoll(arg, &endptr, base);
	return handle_errors(v, endp, endptr);
}
