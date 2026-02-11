flytec_read(flytec_t *flytec)
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(flytec->fd, &readfds);
    int rc;
    do {
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 250 * 1000;
	rc = select(flytec->fd + 1, &readfds, 0, 0, &timeout);
    } while (rc == -1 && errno == EINTR);
    if (rc == -1)
	DIE("select", errno);
    else if (rc == 0)
	error("%s: timeout waiting for data", flytec->device);
    else if (!FD_ISSET(flytec->fd, &readfds))
	DIE("select", 0);
    int n;
    do {
	n = read(flytec->fd, flytec->buf, sizeof flytec->buf);
    } while (n == -1 && errno == EINTR);
    if (n == -1)
	DIE("read", errno);
    else if (n == 0)
	DIE("read", 0);
    flytec->next = flytec->buf;
    flytec->end = flytec->buf + n;
}
