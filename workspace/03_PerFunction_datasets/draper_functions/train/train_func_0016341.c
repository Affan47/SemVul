socket_pending( Socket_t *sock )
{
	int num = -1;

	if (ioctl( sock->fd, FIONREAD, &num ) < 0)
		return -1;
	if (num > 0)
		return num;
#ifdef HAVE_LIBSSL
	if (sock->use_ssl)
		return SSL_pending( sock->ssl );
#endif
	return 0;
}
