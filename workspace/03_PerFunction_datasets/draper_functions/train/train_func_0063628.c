draw (void) {
	int i, w;

	w = (int)(((double)data[0] / (double)SHRT_MAX) * 36.0);
	for (i = 0; i < 36 - w; ++i) {
		switch (buf[i]) {
			case '#':
				buf[i] = '*';
				break;
			case '*':
				buf[i] = '+';
				break;
			case '+':
				buf[i] = '-';
				break;
			default:
				buf[i] = ' ';
		}
	}
	for (i = 36 - w; i < 36; ++i)
		buf[i] = '#';

	buf[36] = buf[37] = ' ';

	w = (int)(((double)data[1] / (double)SHRT_MAX) * 36.0) + 38;
	for (i = 38; i < w; ++i)
		buf[i] = '#';
	for (i = w; i < 38+38; ++i) {
		switch (buf[i]) {
			case '#':
				buf[i] = '*';
				break;
			case '*':
				buf[i] = '+';
				break;
			case '+':
				buf[i] = '-';
				break;
			default:
				buf[i] = ' ';
		}
	}
	fputs (buf, stdout);
	putchar ('\r');
	fflush (stdout);
}
