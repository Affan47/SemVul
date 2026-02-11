rmvfile(path)
CONST char *path;
{
	int n;

	if ((n = checkrmv(path, W_OK)) < 0)
		return((n == CHK_CANCEL) ? APL_CANCEL : APL_IGNORE);
	if (Xunlink(path) < 0) return(APL_ERROR);
#ifndef	_NOEXTRACOPY
	fshowprogress(path);
#endif

	return(APL_OK);
}
