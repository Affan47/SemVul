dhcp_recv_l3_packet(struct dhcp_packet *packet, int fd)
{
	int n;

	memset(packet, 0, sizeof(*packet));

	n = read(fd, packet, sizeof(*packet));
	if (n < 0)
		return -errno;

	if (packet->cookie != htonl(DHCP_MAGIC))
		return -EPROTO;

	check_broken_vendor(packet);

	return n;
}
