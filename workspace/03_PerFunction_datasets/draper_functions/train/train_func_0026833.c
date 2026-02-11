gw_search_result_decompress (DECOMPRESSCTX * dctx,
					unsigned char *data,
					unsigned short len)
{
	int e;
	int ret;

	dctx->z.next_in = data;
	dctx->z.avail_in = len;

	ret = 1;
	do {
		buf_extend (dctx->b, CHUNKSZ);
		dctx->z.avail_out = dctx->b->size - dctx->b->len;
		dctx->z.next_out = dctx->b->ptr + dctx->b->len;

		e = inflate (&dctx->z, Z_NO_FLUSH);
		if (e != Z_OK && e != Z_STREAM_END)
			break;

		dctx->b->len = dctx->z.total_out;
	} while (dctx->z.avail_out == 0);

	dctx->z.next_in = Z_NULL;
	dctx->z.next_out = Z_NULL;

	if (e == Z_OK && ret == 1)
		return 0;


	inflateEnd (&dctx->z);

	return Z_STREAM_END - e;

}
