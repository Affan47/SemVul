fts_children_compat(FTS *sp, int instr)
{
	FTSENT *p;
	int fd;

	if (instr && instr != FTS_NAMEONLY) {
		errno = EINVAL;
		return (NULL);
	}


	p = sp->fts_cur;


	errno = 0;


	if (ISSET(FTS_STOP))
		return (NULL);


	if (p->fts_info == FTS_INIT)
		return (p->fts_link);


	if (p->fts_info != FTS_D )
		return (NULL);


	if (sp->fts_child)
		fts_lfree(sp->fts_child);

	if (instr == FTS_NAMEONLY) {
		SET(FTS_NAMEONLY);
		instr = BNAMES;
	} else
		instr = BCHILD;


	if (p->fts_level != FTS_ROOTLEVEL || p->fts_accpath[0] == '/' ||
	    ISSET(FTS_NOCHDIR))
		return (sp->fts_child = fts_build(sp, instr));

	if ((fd = open(".", O_RDONLY, 0)) < 0)
		return (sp->fts_child = NULL);
	sp->fts_child = fts_build(sp, instr);
	if (fchdir(fd)) {
		(void)close(fd);
		return (NULL);
	}
	(void)close(fd);
	return (sp->fts_child);
}
