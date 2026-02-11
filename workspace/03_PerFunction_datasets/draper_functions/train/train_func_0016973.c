pg_set_block(pgsocket sock)
{
#if !defined(WIN32)
	int			flags;

	flags = fcntl(sock, F_GETFL);
	if (flags < 0 || fcntl(sock, F_SETFL, (long) (flags & ~O_NONBLOCK)))
		return false;
	return true;
#else
	unsigned long ioctlsocket_ret = 0;


	return (ioctlsocket(sock, FIONBIO, &ioctlsocket_ret) == 0);
#endif
}
