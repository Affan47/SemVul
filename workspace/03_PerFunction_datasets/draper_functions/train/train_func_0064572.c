single_valued(const char *type) {
	const char *single[] = { "soa", "cname", NULL };
	int i;

	for (i = 0; single[i]; i++) {
		if (strcasecmp(single[i], type) == 0) {
			return (ISC_TRUE);
		}
	}
	return (ISC_FALSE);
}
