accept(sockaddr *addr, int *len)
{
	int conn;
	for(;;){
		conn = ::accept(nSocket, addr, (socklen_t*)len);
		if (conn == -1) {
			if (errno == EINTR){
				continue;
			}else {
				return SOCKET_ERR;
			}
		}
		break;
	}

	return conn;
}
