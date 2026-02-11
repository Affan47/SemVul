bgzf_compress(void *_dst, int *dlen, void *src, int slen, int level)
{
	uint32_t crc;
	z_stream zs;
	uint8_t *dst = (uint8_t*)_dst;


	zs.zalloc = NULL; zs.zfree = NULL;
	zs.next_in  = (Bytef*)src;
	zs.avail_in = slen;
	zs.next_out = dst + BLOCK_HEADER_LENGTH;
	zs.avail_out = *dlen - BLOCK_HEADER_LENGTH - BLOCK_FOOTER_LENGTH;
	if (deflateInit2(&zs, level, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) return -1;
	if (deflate(&zs, Z_FINISH) != Z_STREAM_END) return -1;
	if (deflateEnd(&zs) != Z_OK) return -1;
	*dlen = zs.total_out + BLOCK_HEADER_LENGTH + BLOCK_FOOTER_LENGTH;

	memcpy(dst, g_magic, BLOCK_HEADER_LENGTH);
	packInt16(&dst[16], *dlen - 1);

	crc = crc32(crc32(0L, NULL, 0L), (Bytef*)src, slen);
	packInt32((uint8_t*)&dst[*dlen - 8], crc);
	packInt32((uint8_t*)&dst[*dlen - 4], slen);
	return 0;
}
