xfl_find_freelist_index(size_t len)
{
	g_assert(size_is_positive(len));
	g_assert(xmalloc_round_blocksize(len) == len);
	g_assert(len <= XMALLOC_MAXSIZE);
	g_assert(len >= XMALLOC_SPLIT_MIN);

	return (len <= XMALLOC_FACTOR_MAXSIZE) ?
		len / XMALLOC_BUCKET_FACTOR - 1 - XMALLOC_BUCKET_OFFSET :
		XMALLOC_BUCKET_CUTOVER +
			(len - XMALLOC_FACTOR_MAXSIZE) / XMALLOC_BLOCK_SIZE;
}
