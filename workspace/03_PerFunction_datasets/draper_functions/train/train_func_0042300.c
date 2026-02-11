unwatchfd(int fd)
{
    int i;

    if (fd < 0 || fd >= FD_SETSIZE)
	return;

    if (FD_ISSET(fd, &poolwatchfds)) {
	FD_CLR(fd, &poolwatchfds);
    }
    if (fd+1 >= poolmaxfd) {
	for(i = poolmaxfd; --i >= 0 && !FD_ISSET(i, &poolwatchfds); )
	    ;
	poolmaxfd = i+1;
    }
    if (FD_ISSET(fd, &poolreadyfds)) {
	FD_CLR(fd, &poolreadyfds);
	poolnready--;
    }
}
