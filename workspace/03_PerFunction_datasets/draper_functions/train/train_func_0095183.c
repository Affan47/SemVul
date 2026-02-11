set_signal_callback(GtkBuilder *builder,
				const char *name, const char *signal_name,
				GCallback handler, gpointer user_data)
{
	GtkWidget *widget;

	widget = (GtkWidget *) gtk_builder_get_object(builder, name);
	if (widget == NULL)
		return;

	g_signal_connect(widget, signal_name, handler, user_data);
}
