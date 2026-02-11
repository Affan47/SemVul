kperror(const char* str)
{
	if (str && *str) {
		fprintf(stderr, "%s: ", str);
	}
	fprintf(stderr, "%s\n", kstrerror(kerrno));
	fflush(stderr);
}
