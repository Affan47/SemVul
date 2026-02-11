connect_ssl(int socket_h, SSL_CTX *client_ctx, SSL **ssl_h, BIO **s_bio, int timeout)
{
	int dummy;


#if 0
	int rc;
	struct timeval to;
	fd_set rfds;

	FD_ZERO(&rfds);
	FD_SET(socket_h, &rfds);

	to.tv_sec  = timeout / 1000;
	to.tv_usec = (timeout - (to.tv_sec * 1000)) * 1000;


	rc = select(socket_h + 1, &rfds, NULL, NULL, &to);
	if (rc == 0)
		return -2;
	else if (rc == -1)
	{
		if (errno == EINTR)
			return -3;
		else
			return -1;
	}
#endif

	*ssl_h = SSL_new(client_ctx);
	*s_bio = BIO_new_socket(socket_h, BIO_NOCLOSE);
	SSL_set_bio(*ssl_h, *s_bio, *s_bio);
	dummy = SSL_connect(*ssl_h);
	if (dummy <= 0)
	{
		sprintf(last_error, "problem starting SSL connection: %d\n", SSL_get_error(*ssl_h, dummy));

		return -1;
	}

	return 0;
}
