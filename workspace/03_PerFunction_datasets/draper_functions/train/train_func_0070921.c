dopopd(trp)
syntaxtree *trp;
{
	char *cp;
	int n;

	if (!dirstack || !dirstack[0]) {
		execerror((trp -> comm) -> argv, NULL, ER_DIREMPTY, 2);
		return(RET_FAIL);
	}
	cp = evalpath(Xstrdup(dirstack[0]), 0);
	n = chdir4(cp, 1, NULL);
	Xfree(cp);
	if (n < 0) {
		execerror((trp -> comm) -> argv, dirstack[0], ER_BADDIR, 0);
		return(RET_FAIL);
	}
	n = countvar(dirstack);
	Xfree(dirstack[0]);
	memmove((char *)&(dirstack[0]), (char *)&(dirstack[1]),
		n * sizeof(char *));
	dodirs(trp);
# ifdef	DEP_PTY
	sendparent(TE_POPVAR, &dirstack);
# endif

	return(RET_SUCCESS);
}
