sys_wait (double delay, int *scan)
{
	double now;
	GtkTerm *t = GTK_TERM(term);
	now=myclock();
	*scan=0;
	t->scan = t->code = 0;
	while (myclock()<now+delay)
	{
		while (gtk_events_pending())
		{
			gtk_main_iteration();
			if (t->scan) {
				*scan = notekey = t->scan;
				t->scan = t->code = 0;
			} else if (t->code) {
				*scan = notekey = t->code;
				t->scan = t->code = 0;
			}
		}
		if (*scan==switch_screen)
		{	if (in_text)
			{	graphic_mode();
				wait_key(scan);
				text_mode();
			}
			else
			{	text_mode();
				wait_key(scan);
				graphic_mode();
			}
			*scan=0;
		}
		if (*scan) return;
		usleep(1);
	}
	*scan=0;
}
