_dospath(path)
CONST char *path;
{
# if	!MSDOS
	if (!dosdrive) return(0);
# endif

	return((Xisalpha(*path) && path[1] == ':') ? *path : 0);
}
