_AuWaitForReadable(AuServer *aud)
{
#ifndef WIN32
#if !defined(AMOEBA) && !defined(_MINIX)
    fd_set r_mask;
    int result;

    FD_ZERO(&r_mask);
    do {
	FD_SET(aud->fd, &r_mask);
	result = select(aud->fd + 1, &r_mask,
			(fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL);
	if (result == -1 && errno != EINTR) _AuIOError(aud);
    } while (result <= 0);
#else

    printf(stderr, "audiolib: _AuWaitForReadable called\n");
    abort();
#endif
#else
    while (1)
    {
	fd_set set;

	FD_ZERO(&set);
	FD_SET(aud->fd, &set);

	if (select(1, &set, NULL, NULL, NULL) == 1)
	    return;

	if (WSAGetLastError() != WSAEINTR)
	    _AuIOError(aud);
    }
#endif
}
