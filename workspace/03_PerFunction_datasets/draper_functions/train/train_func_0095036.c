rmtmpfile(file)
CONST char *file;
{
	if ((Xunlink(file) < 0 && errno != ENOENT) || rmtmpdir(NULL) < 0)
		return(-1);

	return(0);
}
