copy_freqs(int *freqs, int threshold, struct freq_table sortfreqs[])
{
	int ix, ticks, saved = 0;

	for (ix = 0; ix < text_lines; ix++) {
		ticks = freqs [ix];

		if (ticks >= threshold) {
			sortfreqs[saved].ticks = ticks;
			sortfreqs[saved].textindex = ix;
			saved++;
			if (saved >= MAX_NUMLINES)
				break;
		}
	}
	return saved;
}
