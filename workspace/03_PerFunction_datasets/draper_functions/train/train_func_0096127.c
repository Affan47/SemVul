do_write(FILETYPE fd, unsigned char *buff, int siz) {
    int w = write(fd, buff, siz);
    if (w != siz) {
	if (w >= 0) {
	    errno = ENOSPC;
	}
	return -1;
    }
    return siz;
}
