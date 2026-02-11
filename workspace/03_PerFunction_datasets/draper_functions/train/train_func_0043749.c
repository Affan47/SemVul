write_inner(const void *buf, size_t len)
{
    if (len > 0)
	bol = (((const char *)buf)[len - 1] == '\n');
    stream.next_in = (Bytef *)buf;
    stream.avail_in = len;
    while (stream.avail_in != 0)
    {
	if (stream.avail_out == 0)
	{
	    deeper->write(outbuf, Z_BUFSIZE);
	    stream.next_out = outbuf;
	    stream.avail_out = Z_BUFSIZE;
	}
	int err = deflate(&stream, Z_NO_FLUSH);
	if (err != Z_OK)
	    drop_dead(err);
    }
    crc = crc32(crc, (Bytef *)buf, len);
    pos += len;
}
