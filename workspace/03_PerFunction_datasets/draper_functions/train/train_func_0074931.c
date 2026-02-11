sendTo(const void* buffer, int length, const SocketAddress& address, int flags)
{
	int rc;
	do
	{
		if (_sockfd == POCO_INVALID_SOCKET) throw InvalidSocketException();
#if defined(POCO_VXWORKS)
		rc = ::sendto(_sockfd, (char*) buffer, length, flags, (sockaddr*) address.addr(), address.length());
#else
		rc = ::sendto(_sockfd, reinterpret_cast<const char*>(buffer), length, flags, address.addr(), address.length());
#endif
	}
	while (rc < 0 && lastError() == POCO_EINTR);
	if (rc < 0) error();
	return rc;
}
