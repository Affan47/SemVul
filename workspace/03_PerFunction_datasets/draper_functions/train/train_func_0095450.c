gtk_xtext_scrolldown_timeout(GtkXText * xtext)
{
	int p_y, win_height;

	gdk_window_get_pointer(GTK_WIDGET(xtext)->window, 0, &p_y, 0);
	gdk_drawable_get_size(GTK_WIDGET(xtext)->window, 0, &win_height);

	if (p_y > win_height && xtext->adj->value < (xtext->adj->upper - xtext->adj->page_size)) {
		xtext->adj->value++;
		gtk_adjustment_changed(xtext->adj);
		gtk_xtext_render_page(xtext);
		return 1;
	}

	xtext->scroll_tag = 0;
	return 0;
}
