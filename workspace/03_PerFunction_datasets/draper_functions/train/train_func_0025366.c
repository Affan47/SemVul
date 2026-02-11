psql_error(const char *fmt,...)
{
	va_list		ap;

	fflush(stdout);
	if (pset.queryFout != stdout)
		fflush(pset.queryFout);

	if (pset.inputfile)
		fprintf(stderr, "%s:%s:" UINT64_FORMAT ": ", pset.progname, pset.inputfile, pset.lineno);
	va_start(ap, fmt);
	vfprintf(stderr, _(fmt), ap);
	va_end(ap);
}
