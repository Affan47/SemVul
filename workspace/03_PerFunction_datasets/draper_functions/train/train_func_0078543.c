run_remote_archiver(int argc, const char **argv,
			       const char *remote, const char *exec)
{
	char buf[LARGE_PACKET_MAX];
	int fd[2], i, len, rv;
	struct transport *transport;
	struct remote *_remote;

	_remote = remote_get(remote);
	if (!_remote->url[0])
		die("git archive: Remote with no URL");
	transport = transport_get(_remote, _remote->url[0]);
	transport_connect(transport, "git-upload-archive", exec, fd);

	for (i = 1; i < argc; i++)
		packet_write(fd[1], "argument %s\n", argv[i]);
	packet_flush(fd[1]);

	len = packet_read_line(fd[0], buf, sizeof(buf));
	if (!len)
		die("git archive: expected ACK/NAK, got EOF");
	if (buf[len-1] == '\n')
		buf[--len] = 0;
	if (strcmp(buf, "ACK")) {
		if (len > 5 && !prefixcmp(buf, "NACK "))
			die("git archive: NACK %s", buf + 5);
		die("git archive: protocol error");
	}

	len = packet_read_line(fd[0], buf, sizeof(buf));
	if (len)
		die("git archive: expected a flush");


	rv = recv_sideband("archive", fd[0], 1);
	rv |= transport_disconnect(transport);

	return !!rv;
}
