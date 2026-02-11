G__write_data(int fd, int row, int n)
{
    struct fileinfo *fcb = &G__.fileinfo[fd];
    ssize_t nwrite = fcb->nbytes * n;

    if (write(fd, G__.work_buf, nwrite) != nwrite) {
	write_error(fd, row);
	return -1;
    }

    return 0;
}
