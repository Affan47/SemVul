set_address(struct ifreq *ifr, int brd)
{
	int s;

	s = get_ctl_fd();
	if (s < 0)
		return -1;
	if (ioctl(s, brd?SIOCSIFHWBROADCAST:SIOCSIFHWADDR, ifr) < 0) {
		perror(brd?"SIOCSIFHWBROADCAST":"SIOCSIFHWADDR");
		close(s);
		return -1;
	}
	close(s);
	return 0;
}
