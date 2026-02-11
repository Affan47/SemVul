onRead(int fd, int r, void *data)
{
	char buf[4096];
	int n = sSocket.read(buf, 4096);
	LOG("on read, fd=%d, recv=%d", fd, n);
	if(n == SOCKET_ERR){
		nError = sSocket.getError();
		close();
	}else if(n > 0){
		readBuffer.append(buf, n);
		EV_INVOKE(cbRead, this);
	}
}
