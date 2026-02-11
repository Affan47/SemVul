parse_fldarg(char *arg, USHORT ** list)
{
	char  *cp, *np;
	int	result = 1;
	USHORT  *lp;


	for  (cp = arg;  (np = strchr(cp, ','));  cp = np+1)
		result++;

	*list = (USHORT *) malloc((unsigned) (result * sizeof(USHORT)));
	if  (!*list)
		nomem();

	lp = *list;

	for  (cp = arg;  (np = strchr(cp, ','));  cp = np+1)
		*lp++ = atoi(cp);
	*lp = atoi(cp);

	free(arg);
	return  result;
}
