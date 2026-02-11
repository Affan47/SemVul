xmalloc_round_blocksize(size_t len)
{


	if G_UNLIKELY(len > XMALLOC_MAXSIZE)
		return round_pagesize(len);


	if (len <= XMALLOC_FACTOR_MAXSIZE) {
		size_t blen = (len + XMALLOC_FACTOR_MASK) & ~XMALLOC_FACTOR_MASK;
		if G_UNLIKELY(blen < XMALLOC_SPLIT_MIN)
			blen = XMALLOC_SPLIT_MIN;
		return blen;
	}


	return (len + XMALLOC_BLOCK_MASK) & ~XMALLOC_BLOCK_MASK;
}
