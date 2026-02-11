fts_children(sp, instr)
	FTS *sp;
	int instr;
{
	FTSENT *p;
	int fd;

	if (instr != 0 && instr != FTS_NAMEONLY) {
		__set_errno (EINVAL);
		return (NULL);
	}


	p = sp->fts_cur;


	__set_errno (0);


	if (ISSET(FTS_STOP))
		return (NULL);


	if (p->fts_info == FTS_INIT)
		return (p->fts_link);


	if (p->fts_info != FTS_D )
		return (NULL);


	if (sp->fts_child != NULL)
		fts_lfree(sp->fts_child);

	if (instr == FTS_NAMEONLY) {
		SET(FTS_NAMEONLY);
		instr = BNAMES;
	} else
		instr = BCHILD;


	if (p->fts_level != FTS_ROOTLEVEL || p->fts_accpath[0] == '/' ||
	    ISSET(FTS_NOCHDIR))
		return (sp->fts_child = fts_build(sp, instr));

	if ((fd = __open(".", O_RDONLY, 0)) < 0)
		return (NULL);
	sp->fts_child = fts_build(sp, instr);
	if (__fchdir(fd))
		return (NULL);
	(void)__close(fd);
	return (sp->fts_child);
}
