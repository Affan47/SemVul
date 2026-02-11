run(double a)
{
	if (!in) {
		return a;
	}
	if (empty) {
		empty = false;
		for (int i = 0; i < len; i++) {
			in[i] = a;
		}
		out = a * len;
		pint = 0;
		return a;
	}
	out = out - in[pint] + a;
	in[pint] = a;
	if (++pint >= len) pint = 0;
	return out / len;
}
