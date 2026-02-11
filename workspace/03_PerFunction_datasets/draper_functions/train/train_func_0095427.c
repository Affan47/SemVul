__socket_ssl_readv (rpc_transport_t *this, struct iovec *opvector, int opcount)
{
	socket_private_t    *priv = NULL;
	int                  sock = -1;
	int                  ret = -1;

	priv = this->private;
	sock = priv->sock;

	if (priv->use_ssl) {
		ret = ssl_read_one (this, opvector->iov_base, opvector->iov_len);
	} else {
		ret = readv (sock, opvector, opcount);
	}

	return ret;
}
