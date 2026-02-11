buffering_close(int fd)
{
	if (fd == bw_fd && bw_pos > 0) {

		if (blocking_write(fd, bw_outbuf, bw_pos)) {
			perror("write (in buffering_close)");
		}
		bw_fd  = -1;
		bw_pos = 0;
	}
	return(close(fd));
}
