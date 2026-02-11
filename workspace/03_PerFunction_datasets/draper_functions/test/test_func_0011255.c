inflate_buffer(void *in, size_t inlen, void *out, size_t outlen)
{
	z_stream zs;
	int status = Z_OK;

	memset(&zs, 0x0, sizeof(zs));

	zs.next_out  = out;
	zs.avail_out = outlen;

	zs.next_in  = in;
	zs.avail_in = inlen;

	if (inflateInit(&zs) < Z_OK)
		return GIT_ERROR;

	while (status == Z_OK)
		status = inflate(&zs, Z_FINISH);

	inflateEnd(&zs);

	if ((status != Z_STREAM_END) )
		return GIT_ERROR;

	if (zs.total_out != outlen)
		return GIT_ERROR;

	return GIT_SUCCESS;
}
