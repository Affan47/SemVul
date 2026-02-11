compress_buffer_shutdown_output (struct buffer *buf)
{
    struct compress_buffer *cb = buf->closure;
    int zstatus, status;


    static char *buffer = NULL;
    if (!buffer)
	buffer = pagealign_xalloc (BUFFER_DATA_SIZE);

    do
    {
	cb->zstr.avail_out = BUFFER_DATA_SIZE;
	cb->zstr.next_out = (unsigned char *) buffer;

	zstatus = deflate (&cb->zstr, Z_FINISH);
	if (zstatus != Z_OK && zstatus != Z_STREAM_END)
	{
	    compress_error (0, zstatus, &cb->zstr, "deflate finish");
	    return EIO;
	}

	if (cb->zstr.avail_out != BUFFER_DATA_SIZE)
	    buf_output (cb->buf, buffer,
			BUFFER_DATA_SIZE - cb->zstr.avail_out);
    } while (zstatus != Z_STREAM_END);

    zstatus = deflateEnd (&cb->zstr);
    if (zstatus != Z_OK)
    {
	compress_error (0, zstatus, &cb->zstr, "deflateEnd");
	return EIO;
    }

    status = buf_flush (cb->buf, 1);
    if (status != 0)
	return status;

    return buf_shutdown (cb->buf);
}
