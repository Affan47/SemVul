sig_agp_bus_mr(
	struct sig_agp_bus_main *b,
	void *s,
	uint32_t pa,
	unsigned int bs,
	uint32_t *valp
)
{
	struct sig_agp_bus_main_map *m;
	uint32_t *va;
	int (*func)(void *, uint32_t, unsigned int, uint32_t *);
	unsigned int nr;

	m = _sig_agp_bus_map_lookup(b, pa);
	if (! m) {
		m = _sig_agp_bus_map_add(b, pa);
	}
	if (m->va_mr) {
		va = (uint32_t *) m->va_mr + ((pa & 0xffc) >> 2);


		*valp = *va;

		return 0;
	}


	for (nr = 0; ; nr++) {
		if (nr == b->member_count) {
			return -1;
		}
		if (! b->member[nr].f
		 || b->member[nr].s == s) {
			continue;
		}
		func = b->member[nr].f->mr;
		if (func
		 && func(b->member[nr].s, pa, bs, valp) == 0) {
			return 0;
		}
	}
}
