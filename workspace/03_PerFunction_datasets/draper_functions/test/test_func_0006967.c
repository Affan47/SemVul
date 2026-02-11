sig_floppy_wp(
	struct sig_floppy *b,
	void *s
)
{
	unsigned int nr;

	for (nr = 0; ; nr++) {
		int (*func)(void *);

		if (nr == b->member_count) {
			return 1;
		}
		if (b->member[nr].s == s) {
			continue;
		}
		func = b->member[nr].f->wp;
		if (func) {
			return func(b->member[nr].s);
		}
	}
}
