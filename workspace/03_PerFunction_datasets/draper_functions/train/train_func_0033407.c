inittrans(path, len)
CONST char *path;
int len;
{
	transtable *tp;

	if (len < 0) len = strlen(path);
	if (rr_cwd && !strnpathcmp(path, rr_cwd, len) && !rr_cwd[len])
		return(rr_curtbl);
	if (!(tp = readtranstbl(path, len))) return(NULL);

	freetranstbl(rr_curtbl);
	rr_curtbl = tp;
	Xfree(rr_cwd);
	rr_cwd = Xstrndup(path, len);
	Xfree(rr_transcwd);
	rr_transcwd = NULL;

	return(rr_curtbl);
}
