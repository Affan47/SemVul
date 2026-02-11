compress_buffer_flush (void *closure)
{
    struct compress_buffer *cb = closure;


    static char *buffer = NULL;
    if (!buffer)
	buffer = pagealign_xalloc (BUFFER_DATA_SIZE);

    cb->zstr.avail_in = 0;
    cb->zstr.next_in = NULL;

    while (1)
    {
	int zstatus;

	cb->zstr.avail_out = BUFFER_DATA_SIZE;
	cb->zstr.next_out = (unsigned char *) buffer;

	zstatus = deflate (&cb->zstr, Z_SYNC_FLUSH);


	if (zstatus == Z_BUF_ERROR)
	    break;

	if (zstatus != Z_OK)
	{
	    compress_error (0, zstatus, &cb->zstr, "deflate flush");
	    return EIO;
	}

	if (cb->zstr.avail_out != BUFFER_DATA_SIZE)
	    buf_output (cb->buf, buffer,
			BUFFER_DATA_SIZE - cb->zstr.avail_out);


	if (cb->zstr.avail_out > 0)
	    break;
    }


    return buf_flush (cb->buf, 0);
}
