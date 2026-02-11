read_hex_int(const char *file, int *value)
{
	long long res;

	if (read_hex_ll(file, &res))
		return -1;


	if (res > INT_MAX || res < INT_MIN) {
		errmsg("value %lld read from file \"%s\" is out of range",
		       res, file);
		errno = EINVAL;
		return -1;
	}

	*value = res;
	return 0;
}
