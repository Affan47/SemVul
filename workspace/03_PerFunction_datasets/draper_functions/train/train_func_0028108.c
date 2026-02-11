netflush(void)
{
    int n;

    if ((n = nfrontp - nbackp) > 0) {
	DIAG(TD_REPORT,
	     { n += output_data("td: netflush %d chars\r\n", n);
	     });
#ifdef ENCRYPTION
	if (encrypt_output) {
	    char *s = nclearto ? nclearto : nbackp;
	    if (nfrontp - s > 0) {
		(*encrypt_output)((unsigned char *)s, nfrontp-s);
		nclearto = nfrontp;
	    }
	}
#endif


#if 1
	if ((neturg == 0) || (not42 == 0)) {
#endif
	    n = write(net, nbackp, n);
#if 1
	} else {
	    n = neturg - nbackp;


	    if (n > 1) {
		n = send(net, nbackp, n-1, 0);
	    } else {
		n = send(net, nbackp, n, MSG_OOB);
	    }
	}
#endif
    }
    if (n < 0) {
	if (errno == EWOULDBLOCK || errno == EINTR)
	    return;
	cleanup(0);
    }
    nbackp += n;
#ifdef ENCRYPTION
    if (nbackp > nclearto)
	nclearto = 0;
#endif
    if (nbackp >= neturg) {
	neturg = 0;
    }
    if (nbackp == nfrontp) {
	nbackp = nfrontp = netobuf;
#ifdef ENCRYPTION
	nclearto = 0;
#endif
    }
    return;
}
