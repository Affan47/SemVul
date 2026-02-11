hdhomerun_sock_create_udp(void)
{

	hdhomerun_sock_t sock = (hdhomerun_sock_t)socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		return HDHOMERUN_SOCK_INVALID;
	}


	if (fcntl(sock, F_SETFL, O_NONBLOCK) != 0) {
		close(sock);
		return HDHOMERUN_SOCK_INVALID;
	}


	int sock_opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&sock_opt, sizeof(sock_opt));


	return sock;
}
