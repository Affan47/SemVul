gtk_xtext_scrollup_timeout(GtkXText * xtext)
{
	int p_y;

	gdk_window_get_pointer(GTK_WIDGET(xtext)->window, 0, &p_y, 0);

	if (p_y < 0 && xtext->adj->value > 0.0) {
		xtext->adj->value--;
		gtk_adjustment_changed(xtext->adj);
		gtk_xtext_render_page(xtext);
		return 1;
	}

	xtext->scroll_tag = 0;
	return 0;
}
