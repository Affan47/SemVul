decompress_peek(hFILE *fp, unsigned char *dest, size_t destsize)
{


	unsigned char buffer[512];
	z_stream zs;
	ssize_t npeek = hpeek(fp, buffer, sizeof buffer);

	if (npeek < 0) return 0;

	zs.zalloc = NULL;
	zs.zfree = NULL;
	zs.next_in = buffer;
	zs.avail_in = npeek;
	zs.next_out = dest;
	zs.avail_out = destsize;
	if (inflateInit2(&zs, 31) != Z_OK) return 0;

	while (zs.total_out < destsize)
		if (inflate(&zs, Z_SYNC_FLUSH) != Z_OK) break;

	destsize = zs.total_out;
	inflateEnd(&zs);

	return destsize;
}
