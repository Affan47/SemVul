addr2type(const char *address)
{
	struct stat st;

	if (stat(address, &st) < 0) {


		if (strncmp("localhost:", address, 10) == 0)
			return TCP_SOCKET_PROXY;
		if (strncmp("x00", address, 3) != 0)
			return UNKNOWN_PROXY_TYPE;
		else
			return UNIX_SOCKET_PROXY;
	} else {

		if (S_ISCHR(st.st_mode) && strncmp("/dev/", address, 4) == 0)
			return TTY_PROXY;
		else if (S_ISSOCK(st.st_mode))
			return UNIX_SOCKET_PROXY;
		else
			return UNKNOWN_PROXY_TYPE;
	}
}
