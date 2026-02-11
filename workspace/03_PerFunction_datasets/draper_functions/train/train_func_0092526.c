shm_ack(client_t *client)
{
	struct pollfd pfd;
	int err;
	char buf[1];
	pfd.fd = client->ctrl_fd;
	pfd.events = POLLHUP;
	if (poll(&pfd, 1, 0) == 1)
		return -EBADFD;
	err = write(client->ctrl_fd, buf, 1);
	if (err != 1)
		return -EBADFD;
	return 0;
}
