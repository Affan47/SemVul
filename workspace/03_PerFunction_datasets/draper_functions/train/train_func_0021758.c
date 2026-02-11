isns_bitvector_is_empty(const isns_bitvector_t *bv)
{
	uint32_t	*wp, *end;

	if (bv == NULL || bv->ib_count == 0)
		return 1;


	wp = bv->ib_words;
	end = wp + bv->ib_count;
	while (wp < end) {
		unsigned int	rlen;

		rlen = wp[1];
		wp += 2;

		while (rlen--) {
			if (*wp++)
				return 0;
		}
		isns_assert(wp <= end);
	}

	return 1;
}
