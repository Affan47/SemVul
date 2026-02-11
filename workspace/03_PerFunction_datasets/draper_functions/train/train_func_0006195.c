add_device(const char *info)
{
	struct netdev *dev;
	int i;

	dev = malloc(sizeof(struct netdev));
	if (dev == NULL) {
		fprintf(stderr, "%s: out of memory\n", progname);
		longjmp(abort_buf, 1);
	}

	memset(dev, 0, sizeof(struct netdev));
	dev->caps = default_caps;

	if (parse_device(dev, info) == 0)
		goto bail;

	if (netdev_init_if(dev) == -1)
		goto bail;

	if (bootp_init_if(dev) == -1)
		goto bail;

	printf("IP-Config: %s hardware address", dev->name);
	for (i = 0; i < dev->hwlen; i++)
		printf("%c%02x", i == 0 ? ' ' : ':', dev->hwaddr[i]);
	printf(" mtu %d%s%s\n", dev->mtu,
	       dev->caps & CAP_DHCP ? " DHCP" :
	       dev->caps & CAP_BOOTP ? " BOOTP" : "",
	       dev->caps & CAP_RARP ? " RARP" : "");
	return dev;
bail:
	free(dev);
	return NULL;
}
