PerlIOStdio_dup(pTHX_ PerlIO *f, PerlIO *o, CLONE_PARAMS *param, int flags)
{


    if ((f = PerlIOBase_dup(aTHX_ f, o, param, flags))) {
	FILE *stdio = PerlIOSelf(o, PerlIOStdio)->stdio;
	const int fd = fileno(stdio);
	char mode[8];
	if (flags & PERLIO_DUP_FD) {
	    const int dfd = PerlLIO_dup(fileno(stdio));
	    if (dfd >= 0) {
		stdio = PerlSIO_fdopen(dfd, PerlIO_modestr(o,mode));
		goto set_this;
	    }
	    else {
		NOOP;


	    }
	}
    	stdio = PerlSIO_fdopen(fd, PerlIO_modestr(o,mode));
    set_this:
	PerlIOSelf(f, PerlIOStdio)->stdio = stdio;
        if(stdio) {
	    PerlIOUnix_refcnt_inc(fileno(stdio));
        }
    }
    return f;
}
