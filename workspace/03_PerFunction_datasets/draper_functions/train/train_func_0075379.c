urlsplitpath(buf, size, path)
char *buf;
ALLOC_T size;
CONST char *path;
{
	CONST char *cp;

	if (*path != _SC_) {
		errno = EINVAL;
		return(NULL);
	}
	else if (!(cp = strrdelim(&(path[1]), 0))) {
		if (buf) copyrootpath(buf);
		cp = (path[1]) ? &(path[1]) : curpath;
	}
	else if (buf && Xsnprintf(buf, size, "%-.*s", cp - path, path) < 0)
		return(NULL);
	else if (!*(++cp)) cp = curpath;

	return(cp);
}
