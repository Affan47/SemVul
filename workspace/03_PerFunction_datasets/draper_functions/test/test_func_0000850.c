make_local_socket(const char *filename)
{
	size_t l = strlen(filename);
	size_t size = offsetof(struct sockaddr_un, sun_path) + l;
	struct sockaddr_un *addr = alloca(size);
	int sock;

	sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock < 0) {
		SYSERR("socket failed");
		return -errno;
	}

	addr->sun_family = AF_LOCAL;
	memcpy(addr->sun_path, filename, l);

	if (connect(sock, (struct sockaddr *) addr, size) < 0) {
		SYSERR("connect failed");
		return -errno;
	}
	return sock;
}
