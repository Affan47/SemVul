zfile_zuncompress (void *dst, int dstsize, struct zfile *src, int srcsize)
{
	z_stream zs;
	int v;
	uae_u8 inbuf[4096];
	int incnt;

	memset (&zs, 0, sizeof (zs));
	if (inflateInit_ (&zs, ZLIB_VERSION, sizeof (z_stream)) != Z_OK)
		return 0;
	zs.next_out = (Bytef*)dst;
	zs.avail_out = dstsize;
	incnt = 0;
	v = Z_OK;
	while (v == Z_OK && zs.avail_out > 0) {
		if (zs.avail_in == 0) {
			int left = srcsize - incnt;
			if (left == 0)
				break;
			if (left > sizeof (inbuf))
				left = sizeof (inbuf);
			zs.next_in = inbuf;
			zs.avail_in = zfile_fread (inbuf, 1, left, src);
			incnt += left;
		}
		v = inflate (&zs, 0);
	}
	inflateEnd (&zs);
	return 0;
}
