dib0090_set_default_config(struct dib0090_state *state, const u16 * n)
{
	u16 l, r;

	l = pgm_read_word(n++);
	while (l) {
		r = pgm_read_word(n++);
		do {
			dib0090_write_reg(state, r, pgm_read_word(n++));
			r++;
		} while (--l);
		l = pgm_read_word(n++);
	}
}
