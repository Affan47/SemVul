check_linear_format(const snd_pcm_format_mask_t *format_mask, int wid, int sgn, int ed)
{
	int e, s;
	if (! linear_format_widths[wid - 1])
		return SND_PCM_FORMAT_UNKNOWN;
	for (e = 0; e < 2; e++) {
		for (s = 0; s < 2; s++) {
			int pw = ((wid + 7) / 8) * 8;
			for (; pw <= 32; pw += 8) {
				snd_pcm_format_t f;
				f = snd_pcm_build_linear_format(wid, pw, sgn, ed);
				if (f != SND_PCM_FORMAT_UNKNOWN &&
				    snd_pcm_format_mask_test(format_mask, f))
					return f;
			}
			sgn = !sgn;
		}
		ed = !ed;
	}
	return SND_PCM_FORMAT_UNKNOWN;
}
