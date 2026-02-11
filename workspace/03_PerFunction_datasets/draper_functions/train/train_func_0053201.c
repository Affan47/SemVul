do_tcp_rcv(struct ncp_server *server, void *buffer, size_t len)
{
	int result;

	if (buffer) {
		result = _recv(server->ncp_sock, buffer, len, MSG_DONTWAIT);
	} else {
		static unsigned char dummy[1024];

		if (len > sizeof(dummy)) {
			len = sizeof(dummy);
		}
		result = _recv(server->ncp_sock, dummy, len, MSG_DONTWAIT);
	}
	if (result < 0) {
		return result;
	}
	if (result > len) {
		pr_err("tcp: bug in recvmsg (%u > %Zu)\n", result, len);
		return -EIO;
	}
	return result;
}
