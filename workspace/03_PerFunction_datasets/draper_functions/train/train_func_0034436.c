handler_select_set(void *_h, int fd, void *_s)
{
	if (fd == -1)
		return 1;

	handler *h = (handler*)_h;
	FD_SET(fd, &h->rfds);

	if (fd > h->hi)
		h->hi = fd;

	return 1;
}
