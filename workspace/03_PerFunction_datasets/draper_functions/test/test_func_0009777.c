addEventListener(int fd, int event, const IOHandler &cb, void *data)
{
	if(fd < 0) return;
	if(fd >= nSize) resize(fd);

	IOEvent *ev = pEvents + fd;
	if(pPoll->add(fd, event) == -1){
		return ;
	}

	ev->mask|= event;
	ev->data = data;
	if (event & EV_IO_READ) ev->cbRead = cb;
	if (event & EV_IO_WRITE) ev->cbWrite = cb;
	if (fd > nMaxfd) nMaxfd = fd;

	return ;
}
