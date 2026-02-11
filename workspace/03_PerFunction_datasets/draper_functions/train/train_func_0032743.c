krb5_copy_encrypted (kx_context *kc, int fd1, int fd2)
{
    for (;;) {
	fd_set fdset;
	int ret;

	if (fd1 >= FD_SETSIZE || fd2 >= FD_SETSIZE) {
	    krb5_warnx (CONTEXT(kc), "fd too large");
	    return 1;
	}

	FD_ZERO(&fdset);
	FD_SET(fd1, &fdset);
	FD_SET(fd2, &fdset);

	ret = select (max(fd1, fd2)+1, &fdset, NULL, NULL, NULL);
	if (ret < 0 && errno != EINTR) {
	    krb5_warn (CONTEXT(kc), errno, "select");
	    return 1;
	}
	if (FD_ISSET(fd1, &fdset)) {
	    ret = copy_out (kc, fd1, fd2);
	    if (ret <= 0)
		return ret;
	}
	if (FD_ISSET(fd2, &fdset)) {
	    ret = copy_in (kc, fd2, fd1);
	    if (ret <= 0)
		return ret;
	}
    }
}
