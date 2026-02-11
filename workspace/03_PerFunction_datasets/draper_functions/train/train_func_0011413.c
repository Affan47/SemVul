Lsharp_vertical_bar_reader()
{
	int c;
	int level = 0;

	check_arg(3);
	if (vs_base[2] != Cnil && !READsuppress)
		extra_argument('|');
	vs_popp;
	vs_popp;
	for (;;) {
		c = readc_stream(vs_base[0]);
	L:
		if (c == '#') {
			c = readc_stream(vs_base[0]);
			if (c == '|')
				level++;
		} else if (c == '|') {
			c = readc_stream(vs_base[0]);
			if (c == '#') {
				if (level == 0)
					break;
				else
					--level;
			} else
				goto L;
		}
	}
	vs_popp;
	vs_base[0] = Cnil;

}
