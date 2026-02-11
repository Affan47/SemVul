parse_double(const char* start, const char* end, double* out) {
	char *endptr;
	double val = strtod(start, &endptr);

	if (endptr != end)
		return 0;

	*out = val;
	return 1;
}
