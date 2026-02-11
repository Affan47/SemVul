verror(const char *const string, va_list args)
{


	fprintf(stderr, _("\"%s\", line %d: "), filename, linenum);
	vfprintf(stderr, string, args);
	if (rfilename != NULL)
		(void) fprintf(stderr, _(" (rule from \"%s\", line %d)"),
			rfilename, rlinenum);
	(void) fprintf(stderr, "\n");
	++errors;
}
