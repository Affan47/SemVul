FileStat(CONSFILE *cfp, struct stat *buf)
#else
FileStat(cfp, buf)
    CONSFILE *cfp;
    struct stat *buf;
#endif
{
    int retval = 0;

    if (cfp->errored == FLAGTRUE)
	return -1;

    switch (cfp->ftype) {
	case simpleFile:
	    retval = fstat(cfp->fd, buf);
	    break;
	case simplePipe:
	    retval = -1;
	    break;
	case simpleSocket:
	    retval = fstat(cfp->fd, buf);
	    break;
#if HAVE_OPENSSL
	case SSLSocket:
	    retval = -1;
	    break;
#endif
	default:
	    retval = -1;
	    break;
    }

    if (retval < 0)
	cfp->errored = FLAGTRUE;

    return retval;
}
