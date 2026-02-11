do_raw(volume* vol, hfsp_fork_raw *fork, UInt8 forktype,
	    UInt32 cnid, int ofile)
{
    UInt64	total    = fork->total_size;
    UInt32	blksize  = vol -> blksize;
    size_t	size, bytes;
    blockiter	iter;
    char	buf[blksize];

    blockiter_init(&iter, vol, fork, forktype, cnid);


    while (total > 0)
    {
	UInt32	block	= blockiter_curr(&iter);
	int	result  = volume_readinbuf(vol, buf, block);
	void*	p	= buf;
	size	= total > blksize ? blksize : total;
	if (result)
	{
	    ERROR(errno, hfsp_error);
	    return result;
	}

	bytes = write(ofile, p, size);

	total -= size;

	if (bytes != size)
	{
	    if (bytes == -1)
		ERROR(errno, "error writing data");
	    else
		ERROR(EIO, "wrote incomplete chunk");
	    return -1;
	}
	if (blockiter_next(&iter))
	    break;
    }

    return 0;
}
