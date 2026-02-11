rfbListenOnUDPPort(int port,
                   in_addr_t iface)
{
    struct sockaddr_in addr;
    int sock;
    int one = 1;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = iface;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	return -1;
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
		   (char *)&one, sizeof(one)) < 0) {
	return -1;
    }
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	return -1;
    }

    return sock;
}
