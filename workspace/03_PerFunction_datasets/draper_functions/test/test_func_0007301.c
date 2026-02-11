net_ssl_timeout_read(struct net_serv_t * serv, int usec)
{
	int ret = 0;
	fd_set in;
	size_t bytes_read = 0;
	struct timeval timeout;
	int cnt = 0;

	if (!serv || serv->max_sock == -1 || serv->sock == -1 ||
	    !serv->buf || serv->client == -1) {
		return -EINVAL;
	}

	memset(serv->buf, 0, serv->buf_len);
	serv->buf_off = 0;
	while (1) {
		memset(&timeout, 0, sizeof(timeout));
		timeout.tv_sec = 0;
		timeout.tv_usec = usec;
		FD_ZERO(&in);
		FD_SET(serv->client, &in);

		if (cnt > 400) {
			ret = EPERM;
			fprintf(stderr, "Someone is slowing us down... kill it!");
			goto done;
		}

		switch(select(serv->max_sock+1, &in, NULL, NULL, &timeout)) {
			case 0:
				ret = 0;
				goto done;
			case 1:
				bytes_read =
					SSL_read(serv->ssl, serv->buf + serv->buf_off,
					         serv->buf_len - serv->buf_off);
				serv->buf_off += bytes_read;
				cnt += 1;
				break;
			default:
				ret = EIO;
				goto done;
		}
	}

done:
    return ret*-1;
}
