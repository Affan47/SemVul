safemvfile(src, dest, stp1, stp2)
CONST char *src, *dest;
struct stat *stp1, *stp2;
{
	if (Xrename(src, dest) >= 0) {
#ifndef	_NOEXTRACOPY
		fshowprogress(dest);
#endif
		return(0);
	}
	if (errno != EXDEV || s_isdir(stp1)) return(-1);
	if (safecpfile(src, dest, stp1, stp2) < 0 || Xunlink(src) < 0)
		return(-1);

	stp1 -> st_nlink = (TCH_MODE | TCH_UID | TCH_GID
		| TCH_ATIME | TCH_MTIME | TCH_IGNOREERR);
	return (touchfile(dest, stp1));
}
