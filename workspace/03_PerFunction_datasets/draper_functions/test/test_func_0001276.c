apply_integer(const char* key, const char* data, int* target, int* min, int* max)
{
	char* endptr;
	int val;
	errno = 0;
	val = strtol(data, &endptr, 10);

	if (((errno == ERANGE && (val == INT_MAX || val == INT_MIN)) || (errno != 0 && val == 0)) || endptr == data)
			return 0;

	if (min && val < *min)
		return 0;

	if (max && val > *max)
		return 0;

	*target = val;
	return 1;
}
