reset (int argc, char **argv)
{
    fd_set mask;
    int nfnd = 1;

    FD_ZERO (&mask);
    while (nfnd > 0) {
	int fd = fileno(cin);

	if (fd >= FD_SETSIZE)
	    errx (1, "fd too large");
	FD_SET (fd, &mask);
	if ((nfnd = empty (&mask, 0)) < 0) {
	    warn ("reset");
	    code = -1;
	    lostpeer(0);
	} else if (nfnd) {
	    getreply(0);
	}
    }
}
