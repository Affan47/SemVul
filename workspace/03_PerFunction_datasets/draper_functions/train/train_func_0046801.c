ct_buf_put(ct_buf_t *bp, const void *mem, size_t len)
{
	if (len > bp->size - bp->tail) {
		bp->overrun = 1;
		return -1;
	}
	if (mem)
		memcpy(bp->base + bp->tail, mem, len);
	bp->tail += len;
	return len;
}
