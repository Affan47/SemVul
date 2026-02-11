bind(const SocketAddress& address, bool reuseAddress)
{
	if (_sockfd == POCO_INVALID_SOCKET)
	{
		init(address.af());
	}
	if (reuseAddress)
	{
		setReuseAddress(true);
		setReusePort(true);
	}
#if defined(POCO_VXWORKS)
	int rc = ::bind(_sockfd, (sockaddr*) address.addr(), address.length());
#else
	int rc = ::bind(_sockfd, address.addr(), address.length());
#endif
	if (rc != 0) error(address.toString());
}
