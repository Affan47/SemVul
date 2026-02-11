ser_on_read(int fd, void *data, int mask)
{
	char buf[4096];
	int rdlen;
	struct ser_server *ser = data;

	rdlen = read(fd, buf, sizeof(buf));
	if (rdlen <= 0 &&
	    !(errno == EAGAIN || errno == EINTR)) {

		clog(CL_ERROR, "Read from %d failed\n", fd);
		ser_failed_port(ser, fd);
		return;
	}

	if (rdlen > 0) {
		int ret;

		ret = ser_tcp_write_all(ser, buf, rdlen);
		if (ret < 0)
			ser_stop(ser);
	}
}
