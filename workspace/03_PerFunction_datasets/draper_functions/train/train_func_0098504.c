inflate_buffer(void *in, size_t inlen, void *out, size_t outlen)
{
	z_stream zs;
	int status = Z_OK;

	memset(&zs, 0x0, sizeof(zs));

	zs.next_out = out;
	zs.avail_out = (uInt)outlen;

	zs.next_in = in;
	zs.avail_in = (uInt)inlen;

	if (inflateInit(&zs) < Z_OK) {
		giterr_set(GITERR_ZLIB, "Failed to inflate buffer");
		return -1;
	}

	while (status == Z_OK)
		status = inflate(&zs, Z_FINISH);

	inflateEnd(&zs);

	if (status != Z_STREAM_END  ||
		zs.total_out != outlen)
	{
		giterr_set(GITERR_ZLIB, "Failed to inflate buffer. Stream aborted prematurely");
		return -1;
	}

	return 0;
}
