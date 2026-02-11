safemove(path)
CONST char *path;
{
	struct stat st1, st2;
	char dest[MAXPATHLEN];
	int n;

	if ((n = checkdupl(path, dest, &st1, &st2)) < 0
	|| (n = checkrmv(path, W_OK)) < 0)
		return((n == CHK_CANCEL) ? APL_CANCEL : APL_IGNORE);
	if (safemvfile(path, dest, &st1, &st2) < 0) return(APL_ERROR);

	return(APL_OK);
}
