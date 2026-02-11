create_outfile()
{
    struct stat	ostat;
    int flags = O_WRONLY | O_CREAT | O_EXCL;

    for (;;) {

	if (check_ofname() != OK) {
	    close(ifd);
	    return ERROR;
	}

	remove_ofname = 1;
	ofd = open(ofname, flags, RW_USER);
	if (ofd == -1) {
	    perror(ofname);
	    close(ifd);
	    exit_code = ERROR;
	    return ERROR;
	}


	if (fstat(ofd, &ostat) != 0) {
	    fprintf(stderr, "%s: ", progname);
	    perror(ofname);
	    close(ifd); close(ofd);
	    unlink(ofname);
	    exit_code = ERROR;
	    return ERROR;
	}
	if (!name_too_long(ofname, &ostat)) return OK;

	if (decompress) {

	    WARN((stderr, "%s: %s: warning, name truncated\n",
		  progname, ofname));
	    return OK;
	}
	close(ofd);
	unlink(ofname);
	shorten_name(ofname);
    }
}
