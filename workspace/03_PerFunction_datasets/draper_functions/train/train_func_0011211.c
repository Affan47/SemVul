dib8000_viterbi_state(struct dib8000_state *state, u8 onoff)
{
	u16 tmp;

	tmp = dib8000_read_word(state, 771);
	if (onoff)
		dib8000_write_word(state, 771, tmp & 0xfffd);
	else
		dib8000_write_word(state, 771, tmp | (1<<1));
}
