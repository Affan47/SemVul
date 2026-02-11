set_nonblock(int fd, unsigned char v)
{
#ifndef __WIN32__
	int f = fcntl(fd, F_GETFL);
	return f == -1 ? f : fcntl(fd, F_SETFL, (v ? f | O_NONBLOCK : f & ~O_NONBLOCK));
#else
	u_long v_ = (u_long)v;
	errno = 0;
	if (ioctlsocket(fd, FIONBIO, &v_) == SOCKET_ERROR) {
		errno = WSAGetLastError();
		return -1;
	}
	else
		return 0;
#endif
}
