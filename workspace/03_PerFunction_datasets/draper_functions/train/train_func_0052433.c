glade_gtk_label_set_use_underline (GObject *object, const GValue *value)
{
	GladeWidget *glabel;

	glabel = glade_widget_get_from_gobject (object);

	if (g_value_get_boolean (value))
		glade_widget_property_set_sensitive (glabel, "mnemonic-widget", TRUE, NULL);
	else
		glade_widget_property_set_sensitive (glabel, "mnemonic-widget", FALSE, MNEMONIC_INSENSITIVE_MSG);

	gtk_label_set_use_underline (GTK_LABEL (object), g_value_get_boolean (value));
}
