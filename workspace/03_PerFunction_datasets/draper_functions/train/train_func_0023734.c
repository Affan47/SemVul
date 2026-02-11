zlib_compress(unsigned char *dst, unsigned char *src, int n,
			 int nbytes)
{
    int total = nbytes * n;
    int nwrite = G_zlib_compress(G__.work_buf + 1, total,
				 G__.compressed_buf + 1,
				 G__.compressed_buf_size - 1);

    return (nwrite >= total) ? 0 : nwrite;
}
