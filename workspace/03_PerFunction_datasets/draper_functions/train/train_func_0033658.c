make_ppp_unit()
{
	int x, flags;

	FUNC_DEBUG("%s: %d\n", __FUNCTION__,__LINE__);

	if (ppp_dev_fd >= 0) {
		dbglog("in make_ppp_unit, already had /dev/ppp open?");
		close(ppp_dev_fd);
	}
	ppp_dev_fd = open("/dev/ppp", O_RDWR);
	if (ppp_dev_fd < 0)
		fatal("Couldn't open /dev/ppp: %m");
	flags = fcntl(ppp_dev_fd, F_GETFL);
	if (flags == -1
	    || fcntl(ppp_dev_fd, F_SETFL, flags | O_NONBLOCK) == -1)
		warn("Couldn't set /dev/ppp to nonblock: %m");

	ifunit = req_unit;
	x = ioctl(ppp_dev_fd, PPPIOCNEWUNIT, &ifunit);
	if (x < 0 && req_unit >= 0 && errno == EEXIST) {
		warn("Couldn't allocate PPP unit %d as it is already in use", req_unit);
		ifunit = -1;
		x = ioctl(ppp_dev_fd, PPPIOCNEWUNIT, &ifunit);
	}
	if (x < 0)
		error("Couldn't create new ppp unit: %m");
	return x;
}
