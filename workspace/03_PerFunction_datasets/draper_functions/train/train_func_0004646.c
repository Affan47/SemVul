set_ipmode(config * config, ax25_address * call, int ipmode)
{
	struct ax25_route_opt_struct ax25_opt;
	int fds;

	if (!config->ip_adjust_mode)
		return 0;

	ax25_opt.port_addr = config->mycalls[0];
	ax25_opt.dest_addr = *call;
	ax25_opt.cmd = AX25_SET_RT_IPMODE;
	ax25_opt.arg = ipmode ? 'V' : 'D';

	fds = socket(AF_AX25, SOCK_SEQPACKET, 0);

	if (ioctl(fds, SIOCAX25OPTRT, &ax25_opt) < 0) {
		perror("ax25rtd: SIOCAX25OPTRT");
		close(fds);
		return 1;
	}

	close(fds);
	return 0;

}
