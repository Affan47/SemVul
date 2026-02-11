b2n_rshift(b2n_ptr d, b2n_ptr n, unsigned int s)
{
	int	maj, min, size = n->chunks, newsize;
	b2n_ptr	tmp;

	if (!s)
		return b2n_set(d, n);

	maj = s >> CHUNK_SHIFTS;

	newsize = size - maj;

	if (size < maj)
		return b2n_set_null(d);

	min = (CHUNK_BITS - (s & CHUNK_MASK)) & CHUNK_MASK;
	if (min) {
		if ((b2n_sigbit(n) & CHUNK_MASK) > (u_int32_t) min)
			newsize++;

		if (b2n_lshift(d, n, min))
			return -1;
		tmp = d;
	} else
		tmp = n;

	memmove(d->limp, tmp->limp + maj + (min ? 1 : 0),
	    CHUNK_BYTES * newsize);
	if (b2n_resize(d, newsize))
		return -1;

	d->bits = tmp->bits - ((maj + (min ? 1 : 0)) << CHUNK_SHIFTS);
	return 0;
}
