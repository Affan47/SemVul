rcsbuf_cache_open (RCSNode *rcs, off_t pos, FILE **pfp,
		   struct rcsbuffer *prcsbuf)
{
#ifndef HAVE_MMAP
    if (cached_rcs == rcs)
    {
	if (rcsbuf_ftello (&cached_rcsbuf) != pos)
	{
	    if (fseeko (cached_rcsbuf.fp, pos, SEEK_SET) != 0)
		error (1, 0, "cannot fseeko RCS file %s",
		       cached_rcsbuf.filename);
	    cached_rcsbuf.ptr = rcsbuf_buffer;
	    cached_rcsbuf.ptrend = rcsbuf_buffer;
	    cached_rcsbuf.pos = pos;
	}
	*pfp = cached_rcsbuf.fp;


	cached_rcsbuf.filename = rcs->path;

	*prcsbuf = cached_rcsbuf;

	cached_rcs = NULL;


	--rcs->refcount;
	if (rcs->refcount <= 0)
	    error (1, 0, "rcsbuf_cache_open: internal error");
    }
    else
    {
#endif


	if (cached_rcs != NULL)
	    rcsbuf_cache_close ();

	*pfp = CVS_FOPEN (rcs->path, FOPEN_BINARY_READ);
	if (*pfp == NULL)
	    error (1, 0, "unable to reopen `%s'", rcs->path);
#ifndef HAVE_MMAP
	if (pos != 0)
	{
	    if (fseeko (*pfp, pos, SEEK_SET) != 0)
		error (1, 0, "cannot fseeko RCS file %s", rcs->path);
	}
#endif
	rcsbuf_open (prcsbuf, *pfp, rcs->path, pos);
#ifndef HAVE_MMAP
    }
#endif
}
