pipe_cloexec_nonblock(int fd[2])
{
#ifdef WIN32
	return _pipe(fd, 512, _O_BINARY);
#else
	int ret;

#ifdef HAVE_PIPE2
	ret = pipe2(fd, O_CLOEXEC|O_NONBLOCK);
	if (ret >= 0 || errno != ENOSYS)
		return ret;
#endif

	ret = pipe(fd);
	if (ret >= 0) {
		fd_set_cloexec(fd[0], true);
		fd_set_cloexec(fd[1], true);

		fd_set_nonblock(fd[0]);
		fd_set_nonblock(fd[1]);
	}

	return ret;
#endif
}
