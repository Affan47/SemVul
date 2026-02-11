reopendev(uh)
int uh;
{
	httpstat_t *http;
	int duperrno;

	if (isredirect(uh) < 0) return(-1);

	duperrno = errno;
	http = urlhostlist[uh].http;
	uh = urlopendev(http -> location.host, http -> location.type);
	if (uh >= 0) {
		Xfree(urlhostlist[uh].redirect);
		urlhostlist[uh].redirect = Xstrdup(http -> location.path);
	}
	errno = duperrno;

	return(uh);
}
