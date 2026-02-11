sendControlMessage(int to, const char *buff, size_t len, ioTunnel *en)
{
	int n;
	struct pollfd  pfd;
	char *debugMessage;

	pfd.fd = to;
	pfd.events = POLLOUT;

	n = poll(&pfd, 1, 1000*10);

	if( (n == 1) && ( (pfd.revents & POLLERR) || (pfd.revents & POLLHUP) ) ) {
		dc_debug(DC_ERROR, "Unable to send control message, line [%d] is down", to);
		n = -1;
	}else{
		m_lock(&bindLock);
		debugMessage = xstrndup(buff, len);
		debugMessage[len-1] = '\0';
        dc_debug(DC_INFO, "Sending control message: %s (len=%d)", debugMessage, len);
		free(debugMessage);
		n = writen(to, buff, len, en);
		m_unlock(&bindLock);
	}
	return n;
}
