getverbose(Input *in) {
	if (in->fill == ungetfill)
		return get(in);
	else {
		int c = get(in);
		if (c != EOF) {
			char buf = c;
			ewrite(2, &buf, 1);
		}
		return c;
	}
}
