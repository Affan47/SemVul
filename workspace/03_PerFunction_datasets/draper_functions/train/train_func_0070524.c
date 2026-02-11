b_pos(int grace,
		   int stem,
		   int flags,
		   float b)
{
	float d1, d2, shift, depth;
	float top, bot;

	shift = !grace ? BEAM_SHIFT : 3;
	depth = !grace ? BEAM_DEPTH : 1.7;
	if (stem > 0) {
		bot = b - (flags - 1) * shift - depth;
		if (bot > 26)
			return 0;
		top = b;
	} else {
		top = b + (flags - 1) * shift + depth;
		if (top < -2)
			return 0;
		bot = b;
	}

	d1 = rnd6(top - BEAM_OFFSET);
	d2 = rnd6(bot + BEAM_OFFSET);
	if (d1 * d1 > d2 * d2)
		return d2;
	return d1;
}
