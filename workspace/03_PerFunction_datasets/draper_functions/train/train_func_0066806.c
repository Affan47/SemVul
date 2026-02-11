audit_getloginuid(void)
{
	uid_t uid;
	int len, in;
	char buf[16];

	errno = 0;
	in = open("/proc/self/loginuid", O_NOFOLLOW|O_RDONLY);
	if (in < 0)
		return -1;
	do {
		len = read(in, buf, sizeof(buf));
	} while (len < 0 && errno == EINTR);
	close(in);
	if (len < 0 || len >= sizeof(buf))
		return -1;
	buf[len] = 0;
	errno = 0;
	uid = strtol(buf, 0, 10);
	if (errno)
		return -1;
	else
		return uid;
}
