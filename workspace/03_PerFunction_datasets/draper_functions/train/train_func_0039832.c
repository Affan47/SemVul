hdhomerun_sock_bind(hdhomerun_sock_t sock, uint32_t local_addr, uint16_t local_port, bool_t allow_reuse)
{
	int sock_opt = allow_reuse;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sock_opt, sizeof(sock_opt));

	struct sockaddr_in sock_addr;
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(local_addr);
	sock_addr.sin_port = htons(local_port);

	if (bind(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) != 0) {
		return FALSE;
	}

	return TRUE;
}
