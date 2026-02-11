fshowprogress(path)
CONST char *path;
{
	CONST char *cp;
	off_t size;

	if (!(cp = strrdelim(path, 1))) cp = path;
	size = (off_t)DIRENTSIZ(cp);
	showprogress(&size);
}
