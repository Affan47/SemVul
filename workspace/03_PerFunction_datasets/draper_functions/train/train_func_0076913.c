write_compressed(int fd, void *in, unsigned int size, uint32_t *obj_crc)
{
	z_stream stream;
	unsigned long maxsize;
	void *out;

	memset(&stream, 0, sizeof(stream));
	deflateInit(&stream, zlib_compression_level);
	maxsize = deflateBound(&stream, size);
	out = xmalloc(maxsize);


	stream.next_in = in;
	stream.avail_in = size;
	stream.next_out = out;
	stream.avail_out = maxsize;
	while (deflate(&stream, Z_FINISH) == Z_OK);
	deflateEnd(&stream);

	size = stream.total_out;
	write_or_die(fd, out, size);
	*obj_crc = crc32(*obj_crc, out, size);
	free(out);
	return size;
}
