connect(const SocketAddress& address)
{
	if (_sockfd == POCO_INVALID_SOCKET)
	{
		init(address.af());
	}
	int rc;
	do
	{
#if defined(POCO_VXWORKS)
		rc = ::connect(_sockfd, (sockaddr*) address.addr(), address.length());
#else
		rc = ::connect(_sockfd, address.addr(), address.length());
#endif
	}
	while (rc != 0 && lastError() == POCO_EINTR);
	if (rc != 0)
	{
		int err = lastError();
		error(err, address.toString());
	}
}
