PerlIO_debug(const char *fmt, ...)
{
    va_list ap;
    dSYS;
    va_start(ap, fmt);
    if (!PL_perlio_debug_fd) {
	if (!TAINTING_get &&
	    PerlProc_getuid() == PerlProc_geteuid() &&
	    PerlProc_getgid() == PerlProc_getegid()) {
	    const char * const s = PerlEnv_getenv("PERLIO_DEBUG");
	    if (s && *s)
		PL_perlio_debug_fd
		    = PerlLIO_open3(s, O_WRONLY | O_CREAT | O_APPEND, 0666);
	    else
		PL_perlio_debug_fd = -1;
	} else {


	    PL_perlio_debug_fd = -1;
	}
    }
    if (PL_perlio_debug_fd > 0) {
#ifdef USE_ITHREADS
	const char * const s = CopFILE(PL_curcop);

	char buffer[1024];
	const STRLEN len1 = my_snprintf(buffer, sizeof(buffer), "%.40s:%" IVdf " ", s ? s : "(none)", (IV) CopLINE(PL_curcop));
	const STRLEN len2 = my_vsnprintf(buffer + len1, sizeof(buffer) - len1, fmt, ap);
	PerlLIO_write(PL_perlio_debug_fd, buffer, len1 + len2);
#else
	const char *s = CopFILE(PL_curcop);
	STRLEN len;
	SV * const sv = Perl_newSVpvf(aTHX_ "%s:%" IVdf " ", s ? s : "(none)",
				      (IV) CopLINE(PL_curcop));
	Perl_sv_vcatpvf(aTHX_ sv, fmt, &ap);

	s = SvPV_const(sv, len);
	PerlLIO_write(PL_perlio_debug_fd, s, len);
	SvREFCNT_dec(sv);
#endif
    }
    va_end(ap);
}
