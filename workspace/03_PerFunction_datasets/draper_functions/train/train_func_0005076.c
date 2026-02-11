sig_magneto_optical_atip(
	struct sig_magneto_optical *b,
	void *s,
	struct cd_atip *atip
)
{
	unsigned int nr;

	for (nr = 0; ; nr++) {
		int (*func)(void *, struct cd_atip *);

		if (nr == b->member_count) {
			return -1;
		}
		if (b->member[nr].s == s) {
			continue;
		}
		func = b->member[nr].f->atip;
		if (func) {
			return func(b->member[nr].s, atip);
		}
	}
}
