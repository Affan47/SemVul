Peek(void* buffer, unsigned int size, int& error)
{
	int res = recv(m_fd, (char*)buffer, size, MSG_PEEK);

	if (res == -1)
	{
#ifdef __WXMSW__
		error = ConvertMSWErrorCode(WSAGetLastError());
#else
		error = errno;
#endif
	}
	else
		error = 0;

	return res;
}
