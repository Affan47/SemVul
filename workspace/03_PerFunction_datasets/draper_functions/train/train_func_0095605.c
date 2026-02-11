pg_tzenumerate_start(void)
{
	pg_tzenum  *ret = (pg_tzenum *) palloc0(sizeof(pg_tzenum));
	char	   *startdir = pstrdup(pg_TZDIR());

	ret->baselen = strlen(startdir) + 1;
	ret->depth = 0;
	ret->dirname[0] = startdir;
	ret->dirdesc[0] = AllocateDir(startdir);
	if (!ret->dirdesc[0])
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open directory \"%s\": %m", startdir)));
	return ret;
}
