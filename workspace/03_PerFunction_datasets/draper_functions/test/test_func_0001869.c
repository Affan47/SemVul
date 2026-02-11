lzo_decompress(const unsigned char *src, size_t src_len,
		unsigned char *dst)
{
	size_t dst_len = PAGE_SIZE;
	int ret = lzo1x_decompress_safe(src, src_len, dst, &dst_len);
	return ret == LZO_E_OK ? 0 : ret;
}
