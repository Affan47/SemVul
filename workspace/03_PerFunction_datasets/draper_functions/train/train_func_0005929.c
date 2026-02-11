PerlIOScalar_open(pTHX_ PerlIO_funcs * self, PerlIO_list_t * layers, IV n,
		  const char *mode, int fd, int imode, int perm,
		  PerlIO * f, int narg, SV ** args)
{
    SV *arg = (narg > 0) ? *args : PerlIOArg;
    PERL_UNUSED_ARG(fd);
    PERL_UNUSED_ARG(imode);
    PERL_UNUSED_ARG(perm);
    if (SvROK(arg) || SvPOK(arg)) {
	if (!f) {
	    f = PerlIO_allocate(aTHX);
	}
	if ( (f = PerlIO_push(aTHX_ f, self, mode, arg)) ) {
	    PerlIOBase(f)->flags |= PERLIO_F_OPEN;
	}
	return f;
    }
    return NULL;
}
