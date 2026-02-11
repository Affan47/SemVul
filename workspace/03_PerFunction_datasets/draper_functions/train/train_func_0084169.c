glade_gtk_notebook_get_first_blank_page (GtkNotebook *notebook)
{
	GladeWidget *gwidget;
	GtkWidget   *widget;
	gint         position;

	for (position = 0; position < gtk_notebook_get_n_pages (notebook); position++)
	{
		widget = gtk_notebook_get_nth_page (notebook, position);
		if ((gwidget = glade_widget_get_from_gobject (widget)) != NULL)
		{
 			GladeProperty *property =
				glade_widget_get_property (gwidget, "position");
			gint gwidget_position = g_value_get_int (property->value);

			if ((gwidget_position - position) > 0)
				return position;
		}
	}
	return position;
}
