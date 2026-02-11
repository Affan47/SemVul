blocking(fbuf, block)
    fbuf_t *fbuf;
    int block;
{
    int arg;

    fbuf->nonblocking = !block;
    if (fcntl(fbuf->fd, F_GETFL, &arg) >= 0) {
	if (block) arg |= O_NDELAY;
	else arg &= ~O_NDELAY;
	fcntl(fbuf->fd, F_SETFL, &arg);
    }
}
