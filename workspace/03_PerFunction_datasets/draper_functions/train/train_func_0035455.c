fts_set(sp, p, instr)
	FTS *sp;
	FTSENT *p;
	int instr;
{
	if (instr != 0 && instr != FTS_AGAIN && instr != FTS_FOLLOW &&
	    instr != FTS_NOINSTR && instr != FTS_SKIP) {
		__set_errno (EINVAL);
		return (1);
	}
	p->fts_instr = instr;
	return (0);
}
