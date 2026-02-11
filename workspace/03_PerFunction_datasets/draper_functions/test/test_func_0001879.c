PerlIOUnix_dup(pTHX_ PerlIO *f, PerlIO *o, CLONE_PARAMS *param, int flags)
{
    const PerlIOUnix * const os = PerlIOSelf(o, PerlIOUnix);
    int fd = os->fd;
    if (flags & PERLIO_DUP_FD) {
	fd = PerlLIO_dup(fd);
    }
    if (fd >= 0) {
	f = PerlIOBase_dup(aTHX_ f, o, param, flags);
	if (f) {

	    PerlIOUnix_setfd(aTHX_ f, fd, os->oflags);
	    return f;
	}
    }
    return NULL;
}
