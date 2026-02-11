_bridge_del_compat (const char *iface)
{
	int ret = 0, fd;

	if ((fd = socket (AF_LOCAL, SOCK_STREAM, 0)) < 0) {
		nm_log_err (LOGD_DEVICE, "couldn't open control socket.");
		return -EBADF;
	}

	if (ioctl (fd, SIOCBRDELBR, iface) < 0)
		ret = -errno;

	close (fd);
	return ret;
}
