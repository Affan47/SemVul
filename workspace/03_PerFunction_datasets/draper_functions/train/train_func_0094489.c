get_bsg_major(char *path)
{
	FILE *devfd;
	char majorno[8];
	char dev[64];
	char tmp[16];

	sscanf(path, "/dev/bsg/%s", tmp);
	sprintf(dev, "/sys/class/bsg/%s/dev", tmp);
	devfd = fopen(dev, "r");
	if (!devfd)
		return -1;
	fscanf(devfd, "%s:", majorno);
	fclose(devfd);

	return atoi(majorno);
}
