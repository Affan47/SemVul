inet_get_devname(int sockfd, int index, char *devname)
{
	int ret;
	struct ifreq req;

	req.ifr_ifru.ifru_ivalue = index;
	ret = ioctl(sockfd, SIOCGIFNAME, &req);
	if (ret < 0)
	{
		print_error("get devices name");
		return ret;
	}

	text_copy(devname, req.ifr_ifrn.ifrn_name);

	return 0;
}
