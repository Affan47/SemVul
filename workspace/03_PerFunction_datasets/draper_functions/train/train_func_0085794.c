unix_socket_connect(const char *address)
{
	struct sockaddr_un addr;
	int err, sk;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = PF_UNIX;

	if (strncmp("x00", address, 3) == 0) {


		strncpy(addr.sun_path + 1, address + 3,
						sizeof(addr.sun_path) - 2);
	} else {

		strncpy(addr.sun_path, address, sizeof(addr.sun_path) - 1);
	}


	sk = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sk < 0) {
		err = -errno;
		error("Unix socket(%s) create failed: %s(%d)",
				address, strerror(-err), -err);
		return err;
	}

	if (connect(sk, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		err = -errno;
		error("Unix socket(%s) connect failed: %s(%d)",
				address, strerror(-err), -err);
		close(sk);
		return err;
	}

	return sk;
}
