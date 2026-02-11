string_prefix_is(const char *string, const char *prefix) {
	size_t n;

	if(!string || !prefix) return 0;

	if((n = strlen(prefix)) == 0) return 0;

	if(strncmp(string, prefix, n) == 0) return 1;

	return 0;
}
