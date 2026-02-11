store_hadd(hstore *h, const uuid *u, const void *buf, size_t len)
{
	if (!h || !u || !buf || !len)
		return 0;

	char tmpbuf[256];
	char *dst = tmpbuf;

	if (h->wait_for_write)
		dst += sprintf(dst, "[ %u %u 0 0 ]\n", h->nbr, TR_BEGIN);

	unsigned flags = 0;
	int plen = dst - tmpbuf;
	plen += prefix(dst, h->nbr, u, flags, len);
	uint64_t pos = atomic_addu64(&h->st->eodpos[h->st->idx-1], plen+len);

	if (h->wait_for_write)
	{
		h->wait_for_write = 0;
		h->start_pos = pos;
	}

	int ok = store_write2(h->st, tmpbuf, plen, buf, len, pos);
	return ok;
}
