fd_buffer_output (void *closure, const char *data, size_t have, size_t *wrote)
{
    struct fd_buffer *fd = closure;

    *wrote = 0;

    while (have > 0)
    {
	int nbytes;

	nbytes = write (fd->fd, data, have);

	if (nbytes <= 0)
	{
	    if (! fd->blocking
		&& (nbytes == 0 || blocking_error (errno)))
	    {


		return 0;
	    }


	    if (nbytes == 0)
		return EIO;

	    return errno;
	}

	*wrote += nbytes;
	data += nbytes;
	have -= nbytes;
    }

    return 0;
}
