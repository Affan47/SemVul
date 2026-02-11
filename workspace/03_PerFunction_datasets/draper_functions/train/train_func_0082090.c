rb_pipe(rb_fde_t **F1, rb_fde_t **F2, const char *desc)
{
#ifndef _WIN32
	int fd[2];
	if(number_fd >= rb_maxconnections)
	{
		errno = ENFILE;
		return -1;
	}
	if(pipe(fd) == -1)
		return -1;
	rb_fd_hack(&fd[0]);
	rb_fd_hack(&fd[1]);
	*F1 = rb_open(fd[0], RB_FD_PIPE, desc);
	*F2 = rb_open(fd[1], RB_FD_PIPE, desc);

	if(rb_unlikely(!rb_set_nb(*F1)))
	{
		rb_lib_log("rb_open: Couldn't set FD %d non blocking: %s", fd[0], strerror(errno));
		rb_close(*F1);
		rb_close(*F2);
		return -1;
	}

	if(rb_unlikely(!rb_set_nb(*F2)))
	{
		rb_lib_log("rb_open: Couldn't set FD %d non blocking: %s", fd[1], strerror(errno));
		rb_close(*F1);
		rb_close(*F2);
		return -1;
	}


	return 0;
#else


	return rb_socketpair(AF_INET, SOCK_STREAM, 0, F1, F2, desc);
#endif
}
