forcecpfile(path)
CONST char *path;
{
	struct stat st;
	char dest[MAXPATHLEN];

	if (getdestpath(path, dest, &st) < 0) return(APL_OK);
	if (safecpfile(path, dest, &st, NULL) < 0) return(APL_ERROR);
#ifdef	HAVEFLAGS
	st.st_flags = (u_long)-1;
#endif

	st.st_nlink = (TCH_MODE | TCH_UID | TCH_GID
		| TCH_ATIME | TCH_MTIME | TCH_IGNOREERR);
	if (touchfile(dest, &st) < 0) return(APL_ERROR);

	return(APL_OK);
}
