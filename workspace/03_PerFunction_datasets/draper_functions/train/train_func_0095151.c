check_version(int report) {
	int fd;

	if (report) {
		printf("isdnctrl version %s\n", VERSION);
	}
	fd = open("/dev/isdn/isdninfo", O_RDWR);
	if (fd < 0)
	        fd = open("/dev/isdninfo", O_RDONLY);
	if (fd < 0) {
                perror("Can't open /dev/isdninfo or /dev/isdn/isdninfo");
		exit(-1);
	}
	data_version = ioctl(fd, IIOCGETDVR, 0);
	if (data_version < 0) {
		fprintf(stderr, "Could not get version of kernel ioctl structs!\n");
		fprintf(stderr, "Make sure that you are using the correct version.\n");
		fprintf(stderr, "(Try recompiling isdnctrl).\n");
		exit(-1);
	}
	close(fd);
	if (report) {
		printf("Kernel's view of API-versions:\n");
		printf("ttyI: %d, net: %d, info: %d\n",
			data_version & 0xff,
			(data_version >> 8) & 0xff,
			(data_version >> 16) & 0xff);
		return;
	}
	data_version = (data_version >> 8) & 0xff;

	if (data_version < 4) {
		fprintf(stderr, "Kernel-version too old, terminating.\n");
		fprintf(stderr, "UPDATE YOUR KERNEL.\n");
		exit(-1);
	}
	if (data_version > 6) {
		fprintf(stderr, "Kernel-version newer than isdnctrl-version, terminating.\n");
		fprintf(stderr, "GET A NEW VERSION OF isdn4k-utils.\n");
		exit(-1);
	}
}
