H5_buffer_dump(FILE *stream, int indent, const uint8_t *buf,
    const uint8_t *marker, size_t buf_offset, size_t buf_size)
{
    size_t	u, v;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(stream);
    HDassert(indent >= 0);
    HDassert(buf);
    HDassert(marker);
    HDassert(buf_size > 0);


    HDfprintf(stream, "%*sData follows (`__' indicates free region)...\n",
	    indent, "");
    for(u = 0; u < buf_size; u += 16) {
        uint8_t		c;

	HDfprintf(stream, "%*s %8d: ", indent, "", u + buf_offset);


	for(v = 0; v < 16; v++) {
	    if(u + v < buf_size) {
		if(marker[u + v])
		    HDfprintf(stream, "__ ");
		else {
		    c = buf[buf_offset + u + v];
		    HDfprintf(stream, "%02x ", c);
		}
	    }
            else
		fprintf(stream, "   ");
	    if(7 == v)
		HDfputc(' ', stream);
	}
        HDfputc(' ', stream);


	for(v = 0; v < 16; v++) {
	    if(u + v < buf_size) {
		if(marker[u + v])
		    HDfputc(' ', stream);
		else {
		    c = buf[buf_offset + u + v];
		    if(HDisprint(c))
			HDfputc(c, stream);
		    else
			HDfputc('.', stream);
		}
	    }
	    if(7 == v)
		HDfputc(' ', stream);
	}

	HDfputc('\n', stream);
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
