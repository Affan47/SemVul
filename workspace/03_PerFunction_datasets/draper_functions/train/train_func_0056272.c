v4l2_dup(int fd)
{
	int index = v4l2_get_index(fd);

	if (index == -1)
		return syscall(SYS_dup, fd);

	devices[index].open_count++;

	return fd;
}
