setup_tun(unsigned short addr, int make_default)
{
	int ret;
	struct ifreq ifr;
	char cmd[132];
	FILE *procfile;

	tunfd = open("/dev/net/tun", O_RDWR);
	if (tunfd < 0)
	{
		perror("could not open /dev/net/tun");
		exit(2);
	}
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
	strcpy(ifr.ifr_name, "tap%d");
	ret = ioctl(tunfd, TUNSETIFF, (void *) &ifr);
	if (ret != 0)
	{
		perror("could not configure /dev/net/tun");
		exit(2);
	}
	fprintf(stderr, "using tun device %s\n", ifr.ifr_name);


	sprintf(cmd, "/sbin/ifconfig %s hw ether AA:00:04:00:%02X:%02X allmulti mtu %d up\n",
		ifr.ifr_name, addr & 0xFF, addr>>8, mtu);
	system(cmd);


	sprintf(cmd, "/proc/sys/net/decnet/conf/%s/forwarding", ifr.ifr_name);
	procfile = fopen(cmd, "w");
	if (!procfile)
	{
		fprintf(stderr, "Cannot set forwarding on interface\n");
	}
	else
	{
		fprintf(procfile, "1");
		fclose(procfile);
	}

	sprintf(cmd, "/proc/sys/net/decnet/conf/%s/priority", ifr.ifr_name);
	procfile = fopen(cmd, "w");
	if (!procfile)
	{
		fprintf(stderr, "Cannot set priority on interface\n");
	}
	else
	{
		fprintf(procfile, "%d", router_priority);
		fclose(procfile);
	}

	sprintf(cmd, "/proc/sys/net/decnet/conf/%s/t3", ifr.ifr_name);
	procfile = fopen(cmd, "w");
	if (!procfile)
	{
		fprintf(stderr, "Cannot set hello timer\n");
	}
	else
	{
		fprintf(procfile, "%d", hello_timer);
		fclose(procfile);
	}

	if (make_default)
	{
		procfile = fopen("/proc/sys/net/decnet/default_device", "w+");
		if (!procfile)
		{
			fprintf(stderr, "Cannot set default device\n");
		}
		else
		{
			fgets(old_default, sizeof(old_default), procfile);
			fprintf(procfile, "%s", ifr.ifr_name);
			fclose(procfile);
		}
	}

	return tunfd;
}
