print_layout_page_step(PrintWindow *pw, gint step)
{
	gint max;
	gint page;

	max = print_layout_page_count(pw);
	page = pw->proof_page + step;

	if (page >= max) page = max - 1;
	if (page < 0) page = 0;

	if (page == pw->proof_page) return;

	pw->proof_page = page;
	print_window_layout_size(pw);
}
