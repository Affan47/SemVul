toggle_term_window(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	term_data *td;

	int t;
	const char *s;

	s = gtk_widget_get_name(widget);
	sscanf(s, "term_menu_item_%d", &t);
	td = &data[t];

	if (widget != NULL)
		td->visible = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget));

	if (td->visible)
	{
		gtk_widget_show(td->win);
		term_data_redraw(td);
	}
	else
	{
		gtk_widget_hide(td->win);
	}

	return td->visible;
}
