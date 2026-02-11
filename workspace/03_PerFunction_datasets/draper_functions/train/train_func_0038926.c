doedit(BW *bw, unsigned char *s, void *obj, int *notify)
{
	B *b;

	b = bcheck_loaded(s);

	if (b) {
		if (b->changed && !b->scratch)

			return doedit1(bw, 0, s, notify);
		else

			return doedit1(bw, NO_CODE, s, notify);
	} else

		return doedit1(bw, YES_CODE, s, notify);
}
