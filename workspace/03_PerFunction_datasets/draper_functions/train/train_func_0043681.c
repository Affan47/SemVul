service(int fd_in, int fd_out) {
	char type;
	ssize_t retval;
	do {
		retval = xread(fd_in, &type, 1);
		if (retval < 1) {
			if (retval < 0)
				perror("git-ssh-upload: read ");
			return;
		}
		if (type == 'v' && serve_version(fd_in, fd_out))
			return;
		if (type == 'o' && serve_object(fd_in, fd_out))
			return;
		if (type == 'r' && serve_ref(fd_in, fd_out))
			return;
	} while (1);
}
