toggle_xtra_window(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	int i;

	const char *item_name = gtk_widget_get_name(widget);

	for (i = 0; i < MAX_XTRA_WIN_DATA; i++)
	{
		if (streq(item_name, xtra_menu_names[i]))
		{
			xtra_win_data *xd = &xdata[i];

			if (widget != NULL)
				xd->visible = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget));

			if (xd->visible)
				gtk_widget_show(xd->win);
			else
				gtk_widget_hide(xd->win);
		}
	}

	return(TRUE);
}
