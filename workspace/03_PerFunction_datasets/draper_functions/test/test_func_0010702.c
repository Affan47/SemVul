dhcp_send_kernel_packet(struct dhcp_packet *dhcp_pkt,
				uint32_t source_ip, int source_port,
				uint32_t dest_ip, int dest_port)
{
	struct sockaddr_in client;
	int fd, n, opt = 1;

	enum {
		DHCP_SIZE = sizeof(struct dhcp_packet) -
					EXTEND_FOR_BUGGY_SERVERS,
	};

	fd = socket(PF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
	if (fd < 0)
		return -errno;

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(source_port);
	client.sin_addr.s_addr = htonl(source_ip);
	if (bind(fd, (struct sockaddr *) &client, sizeof(client)) < 0) {
		close(fd);
		return -errno;
	}

	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(dest_port);
	client.sin_addr.s_addr = htonl(dest_ip);
	if (connect(fd, (struct sockaddr *) &client, sizeof(client)) < 0) {
		close(fd);
		return -errno;
	}

	n = write(fd, dhcp_pkt, DHCP_SIZE);

	close(fd);

	if (n < 0)
		return -errno;

	return n;
}
