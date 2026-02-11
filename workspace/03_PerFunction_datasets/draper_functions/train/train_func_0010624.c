PerlIO_teardown(void)
{
    dVAR;
#if 0


#ifdef DEBUGGING
    {


#define PERLIO_TEARDOWN_MESSAGE_BUF_SIZE 64
#define PERLIO_TEARDOWN_MESSAGE_FD 2
	char buf[PERLIO_TEARDOWN_MESSAGE_BUF_SIZE];
	int i;
	for (i = 3; i < PL_perlio_fd_refcnt_size; i++) {
	    if (PL_perlio_fd_refcnt[i]) {
		const STRLEN len =
		    my_snprintf(buf, sizeof(buf),
				"PerlIO_teardown: fd %d refcnt=%d\n",
				i, PL_perlio_fd_refcnt[i]);
		PerlLIO_write(PERLIO_TEARDOWN_MESSAGE_FD, buf, len);
	    }
	}
    }
#endif
#endif


    if (PL_perlio_fd_refcnt_size
        && PL_perlio_fd_refcnt) {
	free(PL_perlio_fd_refcnt);
	PL_perlio_fd_refcnt = NULL;
	PL_perlio_fd_refcnt_size = 0;
    }
}
