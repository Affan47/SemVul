find_file(arg)
CONST char *arg;
{
	char *wild;

	if (arg) wild = Xstrdup(arg);
	else if (!(wild = inputstr(FINDF_K, 0, 0, "*", -1)))
		return(FNC_CANCEL);

#ifndef	_NOARCHIVE
	if (*wild == '/') ;
	else
#endif
	if (strdelim(wild, 1)) {
		warning(ENOENT, wild);
		Xfree(wild);
		return(FNC_CANCEL);
	}
	Xfree(findpattern);
	if (*wild) findpattern = wild;
	else {
		Xfree(wild);
		findpattern = NULL;
	}

	return(FNC_EFFECT);
}
