open_filename(const char *filename, const char *opt, int is_input)
{
	FILE *input;
	if (strcmp(filename, "-") == 0)
		input = (is_input) ? stdin : stdout;
	else {
		input = fopen(filename, opt);
		if (!input) {
			fprintf(stderr, "error: cannot open %s: %s", filename, strerror(errno));
			return NULL;
		}
	}
	return input;
}
