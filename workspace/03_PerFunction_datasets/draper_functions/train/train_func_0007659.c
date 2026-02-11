del_kernel_ax25_route(char *dev, ax25_address * call)
{
	struct ax25_routes_struct ax25_route;
	int fds;
	config *config;

	config = dev_get_config(dev);
	if (config == NULL || !config->ax25_add_route)
		return 0;

	ax25_route.port_addr = config->mycalls[0];
	ax25_route.dest_addr = *call;

	fds = socket(AF_AX25, SOCK_SEQPACKET, 0);

	if (ioctl(fds, SIOCDELRT, &ax25_route) < 0) {
		perror("ax25rtd: AX.25 SIOCDELRT");
		close(fds);
		return 1;
	}

	close(fds);
	return 0;
}
