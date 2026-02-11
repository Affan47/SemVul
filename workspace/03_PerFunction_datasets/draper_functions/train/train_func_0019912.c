searchexecpath(path, search)
CONST char *path, *search;
{
	hashlist *hp;
	int type;

	if ((type = searchhash(&hp, path, search)) & CM_NOTFOUND) return(NULL);
	if (type & CM_FULLPATH) return(Xstrdup(path));
# ifdef	_NOUSEHASH
	return((char *)hp);
# else
	return(Xstrdup(hp -> path));
# endif
}
