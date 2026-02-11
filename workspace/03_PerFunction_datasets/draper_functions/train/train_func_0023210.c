client_on_read(int fd, void *data, int mask)
{
	char buf[4096];
	int rdlen;
	struct ser_client *client = data;
	struct ser_server *ser = client->ser;

	rdlen = read(fd, buf, sizeof(buf));
	if (rdlen <= 0 &&
	    !(errno == EAGAIN || errno == EINTR)) {

		clog(CL_ERROR, "Read from %d failed\n", fd);
		__ser_release_client(ser, client);
		return;
	}
	if (rdlen > 0) {
		if (ser->is_telnet)
			rdlen = tn_parse(&client->tn, buf, rdlen);

		write(ser->ser_fd, buf, rdlen);
	}
}
