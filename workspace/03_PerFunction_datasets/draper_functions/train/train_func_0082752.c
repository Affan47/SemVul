read_inner(void *data, size_t len)
{
    if (end_of_file)
	return 0;

    if (!data)
    {
	bzlib_fatal_error(BZ_PARAM_ERROR);

    }
    if (len == 0)
	return 0;

    stream.avail_out = len;
    stream.next_out = (char *)data;

    for (;;)
    {
	if (stream.avail_in == 0)
	{
	    long n = deeper->read(buf, BUFFER_SIZE);
	    stream.avail_in = n;
	    stream.next_in = buf;
	}

	int err = BZ2_bzDecompress(&stream);
	switch (err)
	{
	case BZ_OK:
	    if
    	    (
		deeper->at_end()
	    &&
		stream.avail_in == 0
	    &&
		stream.avail_out > 0
	    )
	    {
		bzlib_fatal_error(BZ_UNEXPECTED_EOF);

	    }
	    break;

	case BZ_STREAM_END:
	    {
		end_of_file = true;
		int nbytes = (len - stream.avail_out);
		pos += nbytes;
		return nbytes;
	    }

	default:
	    bzlib_fatal_error(err);

	}

	if (stream.avail_out == 0)
	{
	    pos += len;
	    return len;
	}
    }
}
