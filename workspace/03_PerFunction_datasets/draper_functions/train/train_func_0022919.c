read_concat(fz_stream *stm, unsigned char *buf, int len)
{
	struct concat_filter *state = (struct concat_filter *)stm->state;
	int n;
	int read = 0;

	if (len <= 0)
		return 0;

	while (state->current != state->count && len > 0)
	{

		if (state->ws)
		{
			*buf++ = 32;
			read++;
			len--;
			state->ws = 0;
			continue;
		}

		n = fz_read(state->chain[state->current], buf, len);
		read += n;
		buf += n;
		len -= n;


		if (n == 0)
		{
			fz_close(state->chain[state->current]);
			state->current++;
			state->ws = state->pad;
		}
	}

	return read;
}
