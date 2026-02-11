read_cb(evutil_socket_t fd, short which, void *arg)
{
	char ch;
	long idx = (long) arg;

	recv(fd, &ch, sizeof(ch), 0);
	if (idx >= 0)
		send(idx, "e", 1, 0);
	fired++;
}
