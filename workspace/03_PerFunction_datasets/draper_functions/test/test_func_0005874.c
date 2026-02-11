PerlIOUnix_refcnt_dec(int fd)
{
    int cnt = 0;
    if (fd >= 0) {
	dVAR;
#ifdef USE_ITHREADS
	MUTEX_LOCK(&PL_perlio_mutex);
#endif
	if (fd >= PL_perlio_fd_refcnt_size) {

	    Perl_croak_nocontext("refcnt_dec: fd %d >= refcnt_size %d\n",
		       fd, PL_perlio_fd_refcnt_size);
	}
	if (PL_perlio_fd_refcnt[fd] <= 0) {

	    Perl_croak_nocontext("refcnt_dec: fd %d: %d <= 0\n",
		       fd, PL_perlio_fd_refcnt[fd]);
	}
	cnt = --PL_perlio_fd_refcnt[fd];
	PerlIO_debug("refcnt_dec: fd %d refcnt=%d\n", fd, cnt);
#ifdef USE_ITHREADS
	MUTEX_UNLOCK(&PL_perlio_mutex);
#endif
    } else {

	Perl_croak_nocontext("refcnt_dec: fd %d < 0\n", fd);
    }
    return cnt;
}
