dodirs(trp)
syntaxtree *trp;
{
	char path[MAXPATHLEN];
	int i;

	if (getworkdir(path) < 0) return(RET_FAIL);
	kanjifputs(path, Xstdout);
	if (dirstack)
		for (i = 0; dirstack[i]; i++)
			VOID_C Xprintf(" %k", dirstack[i]);
	VOID_C fputnl(Xstdout);

	return(RET_SUCCESS);
}
