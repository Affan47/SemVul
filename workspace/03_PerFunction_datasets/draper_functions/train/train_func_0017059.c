add_fd_to_set(int fd)
{
	if (fd >= 0) {
		FD_SET(fd, &allsock);
		if (maxsock >= 0 && fd > maxsock) {
			prev_maxsock = maxsock = fd;
			if ((rlim_t)fd > rlim_ofile_cur - FD_MARGIN)
				bump_nofile();
		}
	}
}
