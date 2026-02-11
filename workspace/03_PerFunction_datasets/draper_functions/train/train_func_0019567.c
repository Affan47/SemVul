send_client_data(int fd, const char *data, ssize_t sz)
{
	if (use_sideband)
		return send_sideband(1, fd, data, sz, use_sideband);
	if (fd == 3)

		fd = 2;
	if (fd == 2) {

		xwrite(fd, data, sz);
		return sz;
	}
	return safe_write(fd, data, sz);
}
