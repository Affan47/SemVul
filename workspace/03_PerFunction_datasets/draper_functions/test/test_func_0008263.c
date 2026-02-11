symbols_sort(symbols_t *st)
{
	size_t i = 0;
	size_t ocount;
	const void *last = NULL;
	size_t osize, nsize;

	symbols_check(st);

	if G_UNLIKELY(st->sorted || 0 == st->count)
		return 0;

	xqsort(st->base, st->count, sizeof st->base[0], symbol_cmp);

	ocount = st->count;

	while (i < st->count) {
		struct symbol *s = &st->base[i];
		if (last != NULL && s->addr == last) {
			symbols_remove(st, i);
		} else {
			last = s->addr;
			i++;
		}
	}


	osize = st->size * sizeof st->base[0];
	nsize = st->count * sizeof st->base[0];

	if (nsize != 0) {
		st->base = st->once ?
			vmm_resize_not_leaking(st->base, osize, nsize) :
			vmm_resize(st->base, osize, nsize);
	} else {
		vmm_free(st->base, osize);
		st->base = NULL;
	}

	st->size = st->count;
	st->sorted = TRUE;

	return ocount - st->count;
}
