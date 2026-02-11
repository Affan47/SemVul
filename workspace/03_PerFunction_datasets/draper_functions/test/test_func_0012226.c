gpt_probe_signature_devname(char *devname)
{
	int res, fd;
	if ((fd = open(devname, O_RDONLY)) < 0)
		return 0;
	res = gpt_probe_signature_fd(fd);
	close(fd);
	return res;
}
