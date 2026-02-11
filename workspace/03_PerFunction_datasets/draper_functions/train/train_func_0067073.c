PerlIOStdio_fileno(pTHX_ PerlIO *f)
{
    PERL_UNUSED_CONTEXT;

    if (PerlIOValid(f)) {
	FILE * const s = PerlIOSelf(f, PerlIOStdio)->stdio;
	if (s)
	    return PerlSIO_fileno(s);
    }
    errno = EBADF;
    return -1;
}
