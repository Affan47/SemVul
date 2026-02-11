cri_connect_token(void)
{
    int fd;


    fd = __cri_open(CR_CTRL_FILE, O_WRONLY, 0, NULL);
    if (fd < 0) {

        errno = ENOSYS;
        goto out;
    }


    (void)fcntl(fd, F_SETFD, FD_CLOEXEC);


    if (ioctl(fd, CR_OP_VERSION, (CR_MODULE_MAJOR << 16) | CR_MODULE_MINOR) < 0) {


	(void)__cri_close(fd, NULL);
	fd = -1;
    }

out:
    return fd;
}
