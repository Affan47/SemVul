_comedi_ioctl(int fd, int request, void *arg)
{
	int ret;

	ret = ioctl(fd, request, arg);
	if(ret < 0)
		libc_error();
	return ret;
}
