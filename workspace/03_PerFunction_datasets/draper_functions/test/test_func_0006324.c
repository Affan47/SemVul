glade_gtk_tool_button_set_icon (GObject *object, const GValue *value)
{
	GladeWidget *gbutton;
	GObject *pixbuf;
	GtkWidget *image = NULL;

	g_return_if_fail (GTK_IS_TOOL_BUTTON (object));
	gbutton = glade_widget_get_from_gobject (object);

	if ((pixbuf = g_value_get_object (value)))
	{
		image = gtk_image_new_from_pixbuf (GDK_PIXBUF (pixbuf));
		gtk_widget_show (image);
	}
	gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (object), image);
}
