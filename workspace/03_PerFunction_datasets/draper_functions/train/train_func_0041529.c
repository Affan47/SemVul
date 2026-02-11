get_term_size(int *w, int *h)
{
	struct winsize sz;
	memset(&sz, 0, sizeof(sz));

	ioctl(out_fileno, TIOCGWINSZ, &sz);

	if (w) *w = sz.ws_col;
	if (h) *h = sz.ws_row;
}
