sendUrgent(unsigned char data)
{
	if (_sockfd == POCO_INVALID_SOCKET) throw InvalidSocketException();

	int rc = ::send(_sockfd, reinterpret_cast<const char*>(&data), sizeof(data), MSG_OOB);
	if (rc < 0) error();
}
