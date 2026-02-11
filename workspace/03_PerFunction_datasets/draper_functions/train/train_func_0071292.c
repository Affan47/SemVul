uxsel_set(int fd, int rwx, uxsel_callback_fn callback)
{
    struct fd *newfd;

    uxsel_del(fd);

    if (rwx) {
	newfd = snew(struct fd);
	newfd->fd = fd;
	newfd->rwx = rwx;
	newfd->callback = callback;
	newfd->id = uxsel_input_add(fd, rwx);
	add234(fds, newfd);
    }
}
