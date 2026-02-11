do_gcu_resize(void)
{
	int i, rows, cols, y, x;
	term *old_t = Term;

	for (i = 0; i < MAX_TERM_DATA; i++)
	{

		if (use_big_screen && i > 0) break;


		Term_activate(&data[i].t);


		get_gcu_term_size(i, &rows, &cols, &y, &x);
		if (wresize(data[i].win, rows, cols) == OK)
			Term_resize(cols, rows);


		Term_activate(old_t);
	}
	do_cmd_redraw();
}
