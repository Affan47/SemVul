semitrinkle(array const *ary, size_t r, stretch s)
{
	size_t r1 = r - s.c;

	DEBUG(("semitrinkle(%p, %zu, (%u, %s))\n", ary, r, s.b, binary(s.p)));

	if (cmp_items(ary, r, r1) < 0) {
		DEBUG(("\tswap(%p @%zu <=> @%zu b=%u)\n", ary, r, r1, s.b));
		swap_items(ary, r, r1);
		trinkle(ary, r1, s);
	}
}
