tcp_stream_raw_setsockopt (CamelTcpStream *stream,
                           const CamelSockOptData *data)
{
	CamelTcpStreamRaw *raw = CAMEL_TCP_STREAM_RAW (stream);
	CamelTcpStreamRawPrivate *priv = raw->priv;
	PRSocketOptionData sodata;

	memset ((gpointer) &sodata, 0, sizeof (sodata));
	memcpy ((gpointer) &sodata, (gpointer) data, sizeof (CamelSockOptData));

	if (PR_SetSocketOption (priv->sockfd, &sodata) == PR_FAILURE)
		return -1;

	return 0;
}
