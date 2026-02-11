phone_mini_packet(struct phone_pvt *i)
{
	int res;
	char buf[1024];

	res = read(i->fd, buf, sizeof(buf));
	if (res < 1) {
		ast_log(LOG_WARNING, "Read returned %d: %s\n", res, strerror(errno));
		return;
	}
}
