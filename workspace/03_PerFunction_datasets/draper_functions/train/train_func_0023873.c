dev_ioctl_setpipefd(unsigned int logopt, int ioctlfd, int pipefd)
{
	struct autofs_dev_ioctl param;

	if (pipefd == -1) {
		errno = EBADF;
		return -1;
	}

	init_autofs_dev_ioctl(&param);
	param.ioctlfd = ioctlfd;
	param.setpipefd.pipefd = pipefd;

	if (ioctl(ctl.devfd, AUTOFS_DEV_IOCTL_SETPIPEFD, &param) == -1)
		return -1;

	return 0;
}
