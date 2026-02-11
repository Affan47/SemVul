open()
{
#ifdef HAVE_UNIX98
	m = "/dev/ptmx";

	if ((_master = ::open(m.c_str(), O_RDWR|O_NOCTTY)) < 0) {
		serr = strerror(errno);
		return -1;
	}
	if (grantpt(_master) < 0) {
		::close(_master);
		serr = strerror(errno);
		return -1;
	}

	unlockpt(_master);
#ifdef __linux__
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	ptsname_r(_master, buf, sizeof(buf));
	s = buf;
#else
	s = ptsname(_master);
#endif

	if ((_slave = ::open(s.c_str(), O_RDWR|O_NOCTTY)) < 0) {
		::close(_master);
		serr = strerror(errno);
		return -1;
	}
#ifdef __sun__
	ioctl(_slave, I_PUSH, "ptem");
	ioctl(_slave, I_PUSH, "ldterm");
	ioctl(_slave, I_PUSH, "ttcompat");
#endif

#endif
	return 0;
}
