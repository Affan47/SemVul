do_scroll(GdkEventScroll * event)
{
	int x, y;
	gtk_window_get_position (GTK_WINDOW(g_pReciteWord->window), &x, &y);
	if ((event->x_root>=x+Skin->group.wordlist_area.x[0])&&(event->x_root<=x+Skin->group.wordlist_area.x[0]+Skin->group.wordlist_area.w)
		&&(event->y_root>=y+Skin->group.wordlist_area.y[0])&&(event->y_root<=y+Skin->group.wordlist_area.y[0]+Skin->group.wordlist_area.h))
	{
		GtkAdjustment *adj = (GtkAdjustment *)wordlist_adjust;
		gdouble new_value = adj->value + ((event->direction == GDK_SCROLL_UP ||
                                         event->direction == GDK_SCROLL_LEFT) ?
					-adj->page_increment / 2:
					adj->page_increment / 2);
		if (new_value>(adj->upper - adj->page_size))
			new_value = (adj->upper - adj->page_size);
		if (new_value<0)
			new_value=0;
		if (new_value!=adj->value)
		{
			adj->value = new_value;
			g_signal_emit_by_name (wordlist_adjust, "changed");
			on_group_wordlistadjust_valuechanged(adj,this);
		}
	}
}
