fundef_allocate (cptr, file, line)
	struct fundef **cptr;
	const char *file;
	int line;
{
	struct fundef *rval;

	rval = dmalloc (sizeof (struct fundef), file, line);
	if (!rval)
		return 0;
	memset (rval, 0, sizeof *rval);
	return fundef_reference (cptr, rval, file, line);
}
