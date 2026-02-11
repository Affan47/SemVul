lookup_widget_DEPRECATED(GtkWidget * widget, const gchar * widget_name)
{
	GtkWidget *parent, *found_widget;

	for (;;) {
		if (GTK_IS_MENU(widget))
			parent = gtk_menu_get_attach_widget(GTK_MENU(widget));
		else
			parent = widget->parent;
		if (parent == NULL)
			break;
		widget = parent;
	}

	found_widget =
	    (GtkWidget *) gtk_object_get_data(GTK_OBJECT(widget), widget_name);
	if (!found_widget)
		g_warning(_("Widget not found: %s"), widget_name);
	return found_widget;
}
