urlallclose(VOID_A)
{
	int uh, n;

	n = 0;
	for (uh = maxurlhost - 1; uh >= 0; uh--) {
		if (urlhostlist[uh].flags & UFL_CLOSED) continue;
		urlhostlist[uh].nlink = 0;
		if (_urlclosedev(uh, 0) < 0) n = -1;
	}
	maxurlhost = 0;
	Xfree(logheader);
	logheader = NULL;
	authfree();

	return(n);
}
