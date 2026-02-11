toolbar_get_widget_child_by_name(const gchar *name)
{
	GtkWidget *widget = toolbar_get_widget_by_name(name);

	if (G_LIKELY(widget != NULL))
		return gtk_bin_get_child(GTK_BIN(widget));
	else
		return NULL;
}
