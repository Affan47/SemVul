WRITE_SSL(SSL *ssl_h, char *whereto, int len)
{
	int cnt=len;

	while(len>0)
	{
		int rc;

		rc = SSL_write(ssl_h, whereto, len);
		if (rc == -1)
		{
			if (errno != EINTR && errno != EAGAIN)
			{
				sprintf(last_error, "WRITE_SSL: io-error: %s\n", strerror(errno));
				return -1;
			}
		}
		else if (rc == 0)
		{
			return 0;
		}
		else
		{
			whereto += rc;
			len -= rc;
		}
	}

	return cnt;
}
