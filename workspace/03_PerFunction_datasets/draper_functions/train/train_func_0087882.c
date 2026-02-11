retry_writev(fd, srciov, iovcnt)
int fd;
struct iovec *srciov;
int iovcnt;
{
    int n;
    int i;
    int written = 0;
    struct iovec *iov, *baseiov;
    static int iov_max =
#ifdef MAXIOV
	MAXIOV
#else
#ifdef IOV_MAX
	IOV_MAX
#else
	8192
#endif
#endif
	;

    baseiov = iov = (struct iovec *)xmalloc(iovcnt * sizeof(struct iovec));
    for (i = 0; i < iovcnt; i++) {
	iov[i].iov_base = srciov[i].iov_base;
	iov[i].iov_len = srciov[i].iov_len;
    }

    for (;;) {
	while (iovcnt && iov[0].iov_len == 0) {
	    iov++;
	    iovcnt--;
	}

	if (!iovcnt) goto done;

	n = writev(fd, iov, iovcnt > iov_max ? iov_max : iovcnt);
	if (n == -1) {
	    if (errno == EINVAL && iov_max > 10) {
		iov_max /= 2;
		continue;
	    }
	    if (errno == EINTR) continue;
	    written = -1;
	    goto done;
	}

	written += n;

	for (i = 0; i < iovcnt; i++) {
	    if (iov[i].iov_len > (size_t) n) {
		iov[i].iov_base = (char *)iov[i].iov_base + n;
		iov[i].iov_len -= n;
		break;
	    }
	    n -= iov[i].iov_len;
	    iov[i].iov_len = 0;
	}

	if (i == iovcnt) goto done;
    }

done:
    free(baseiov);
    return written;
}
