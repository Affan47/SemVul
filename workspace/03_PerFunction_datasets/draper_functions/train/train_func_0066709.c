filefromprogs(progfuncs_t *progfuncs, progsnum_t prnum, char *fname, int *size, char *buffer)
{
	int num;
	includeddatafile_t *s;
	if (!pr_progstate[prnum].progs)
		return NULL;
	if (pr_progstate[prnum].progs->version != PROG_EXTENDEDVERSION)
		return NULL;
	if (!pr_progstate[prnum].progs->secondaryversion != PROG_SECONDARYVERSION16 &&
		!pr_progstate[prnum].progs->secondaryversion != PROG_SECONDARYVERSION32)
		return NULL;

	num = *(int*)((char *)pr_progstate[prnum].progs + pr_progstate[prnum].progs->ofsfiles);
	s = (includeddatafile_t *)((char *)pr_progstate[prnum].progs + pr_progstate[prnum].progs->ofsfiles+4);
	while(num>0)
	{
		if (!strcmp(s->filename, fname))
		{
			if (size)
				*size = s->size;
			if (!buffer)
				return (char *)0xffffffff;
			return QC_decode(progfuncs, s->compsize, s->size, s->compmethod, (char *)pr_progstate[prnum].progs+s->ofs, buffer);
		}

		s++;
		num--;
	}

	if (size)
		*size = 0;
	return NULL;
}
