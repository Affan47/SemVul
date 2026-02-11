rcsbuf_open (struct rcsbuffer *rcsbuf, FILE *fp, const char *filename,
	     long unsigned int pos)
{
    if (rcsbuf_inuse)
	error (1, 0, "rcsbuf_open: internal error");
    rcsbuf_inuse = 1;

#ifdef HAVE_MMAP
    {


	struct stat fs;
	size_t mmap_off = 0;

	if ( fstat (fileno(fp), &fs) < 0 )
	    error ( 1, errno, "Could not stat RCS archive %s for mapping", filename );

	if (pos)
	{
	    size_t ps = getpagesize ();
	    mmap_off = ( pos / ps ) * ps;
	}


	rcsbuf_buffer = mmap ( NULL, fs.st_size - mmap_off,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE, fileno(fp), mmap_off );
	if ( rcsbuf_buffer == NULL || rcsbuf_buffer == MAP_FAILED )
	    error ( 1, errno, "Could not map memory to RCS archive %s", filename );

	rcsbuf_buffer_size = fs.st_size - mmap_off;
	rcsbuf->ptr = rcsbuf_buffer + pos - mmap_off;
	rcsbuf->ptrend = rcsbuf_buffer + fs.st_size - mmap_off;
	rcsbuf->pos = mmap_off;
    }
#else
    if (rcsbuf_buffer_size < RCSBUF_BUFSIZE)
	expand_string (&rcsbuf_buffer, &rcsbuf_buffer_size, RCSBUF_BUFSIZE);

    rcsbuf->ptr = rcsbuf_buffer;
    rcsbuf->ptrend = rcsbuf_buffer;
    rcsbuf->pos = pos;
#endif
    rcsbuf->fp = fp;
    rcsbuf->filename = filename;
    rcsbuf->vlen = 0;
    rcsbuf->at_string = 0;
    rcsbuf->embedded_at = 0;
}
