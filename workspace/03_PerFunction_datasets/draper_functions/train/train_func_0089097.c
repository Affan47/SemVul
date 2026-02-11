zstream_sync(struct zstream *z, Bytef *src, long len)
{
    VALUE rest;
    int err;

    if (!NIL_P(z->input)) {
	z->stream.next_in = (Bytef*)RSTRING_PTR(z->input);
	z->stream.avail_in = MAX_UINT(RSTRING_LEN(z->input));
	err = inflateSync(&z->stream);
	if (err == Z_OK) {
	    zstream_discard_input(z,
				  RSTRING_LEN(z->input) - z->stream.avail_in);
	    zstream_append_input(z, src, len);
	    return Qtrue;
	}
	zstream_reset_input(z);
	if (err != Z_DATA_ERROR) {
	    rest = rb_str_new((char*)z->stream.next_in, z->stream.avail_in);
	    raise_zlib_error(err, z->stream.msg);
	}
    }

    if (len <= 0) return Qfalse;

    z->stream.next_in = src;
    z->stream.avail_in = MAX_UINT(len);
    err = inflateSync(&z->stream);
    if (err == Z_OK) {
	zstream_append_input(z, z->stream.next_in, z->stream.avail_in);
	return Qtrue;
    }
    if (err != Z_DATA_ERROR) {
	rest = rb_str_new((char*)z->stream.next_in, z->stream.avail_in);
	raise_zlib_error(err, z->stream.msg);
    }
    return Qfalse;
}
