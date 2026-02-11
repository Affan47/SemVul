err_xopen_core(const char *func, const char *fn, const char *mode)
{
	FILE *fp = 0;
	if (strcmp(fn, "-") == 0)
		return (strstr(mode, "r"))? stdin : stdout;
	if ((fp = fopen(fn, mode)) == 0) {
		fprintf(stderr, "[%s] fail to open file '%s'. Abort!\n", func, fn);
		abort();
	}
	return fp;
}
