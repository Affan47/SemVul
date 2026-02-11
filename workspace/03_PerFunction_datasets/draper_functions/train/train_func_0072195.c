find_free_vtno(void)
{
	int vtno;
	int fd = get_vt_fd();

	errno = 0;

	if (ioctl(fd, VT_OPENQRY, &vtno) != 0 || vtno <= 0)
		bb_perror_msg_and_die("can't find open VT");


	return vtno;
}
