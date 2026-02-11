uart_init(const char * dev)
{
	int fd;
	struct termios tios;

	dbg("Initializing interface %d...", nr_iface);

	if (nr_iface >= MAX_IFACE) {
		err("Invalid interface %d should be less MAX supported is %d\n",
				nr_iface, MAX_IFACE-1);
		return -1;
	}

   	if ((fd = open(dev, O_RDWR | O_NOCTTY)) < 0) {
		err("Unable to open %s: %s\n", dev, strerror(errno));
		return -1;
	}
	if (tcgetattr(fd, &tios) < 0) {
		err("Unable to get attr for %s: %s\n", dev, strerror(errno));
		close (fd);
		return -1;
	}
	cfmakeraw(&tios);
	cfsetospeed(&tios, SYSTEM_BAUD);
	cfsetispeed(&tios, SYSTEM_BAUD);
	if (tcsetattr(fd, TCSANOW, &tios) < 0) {
		err("Unable to setattr for %s: %s\n", dev, strerror(errno));
		return -1;
	}
	h_iface[nr_iface] = (void *) fd;
	nr_iface ++;

	dbg("Done\n");
	return nr_iface-1;
}
