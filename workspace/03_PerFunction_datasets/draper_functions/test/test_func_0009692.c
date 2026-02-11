widget_parent_changed (GtkWidget          *widget,
		       GParamSpec         *pspec,
		       GladeWidgetAdaptor *adaptor)
{
	GladeWidget *gwidget = glade_widget_get_from_gobject (widget);


	if (!gwidget)
		return;

	if (gwidget->parent && gwidget->parent->internal == NULL)
		glade_widget_set_action_sensitive (gwidget, "remove_parent", TRUE);
	else
		glade_widget_set_action_sensitive (gwidget, "remove_parent", FALSE);
}
