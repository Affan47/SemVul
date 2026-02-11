free_area(const struct syslinux_memmap *mmap,
			addr_t len, addr_t * start)
{
    const struct syslinux_memmap *best = NULL;
    const struct syslinux_memmap *s;
    addr_t slen, best_len = -1;

    for (s = mmap; s->type != SMT_END; s = s->next) {
	if (s->type != SMT_FREE)
	    continue;
	slen = s->next->start - s->start;
	if (slen >= len) {
	    if (!best || best_len > slen) {
		best = s;
		best_len = slen;
	    }
	}
    }

    if (best) {
	*start = best->start;
	return best_len;
    } else {
	return 0;
    }
}
