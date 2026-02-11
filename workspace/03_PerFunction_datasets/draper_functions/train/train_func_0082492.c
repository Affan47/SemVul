rb_set_buffers(rb_fde_t *F, int size)
{
	if(F == NULL)
		return 0;
	if(setsockopt
	   (F->fd, SOL_SOCKET, SO_RCVBUF, (char *)&size, sizeof(size))
	   || setsockopt(F->fd, SOL_SOCKET, SO_SNDBUF, (char *)&size, sizeof(size)))
		return 0;
	return 1;
}
