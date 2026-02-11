do_local_client_step(int fd, void (*process)(char *buf))
{
	int numbytes;
	char buf[1024];

	memset(buf, 0, sizeof(buf));
	while ((numbytes = recv(fd, buf, sizeof(buf)-1, 0)) > 0) {
		buf[sizeof(buf)-1] = '\0';
		if (process)
			process(buf);
		memset(buf, 0, sizeof(buf));
	}

	return 0;
}
