memBufAppend(MemBuf * mb, const void *buf, int sz)
{
    assert(mb && buf && sz >= 0);
    assert(mb->buf);
    assert(!mb->stolen);

    if (sz > 0) {
	if (mb->size + sz + 1 > mb->capacity)
	    memBufGrow(mb, mb->size + sz + 1);
	assert(mb->size + sz <= mb->capacity);
	xmemcpy(mb->buf + mb->size, buf, sz);
	mb->size += sz;
	mb->buf[mb->size] = '\0';
    }
}
