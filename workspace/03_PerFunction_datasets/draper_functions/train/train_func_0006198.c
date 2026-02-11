label_in_box_new(const char *s, const char *tooltip)
{
	GtkWidget *evbox, *label;

	evbox = gtk_event_box_new();
	label = gtk_label_new(s);
	gtk_misc_set_padding(GTK_MISC(label), 1, 1);
	gtk_container_add(GTK_CONTAINER(evbox), label);
	if (tooltip)
		gtk_widget_set_tooltip_markup(evbox, tooltip);
	return label;
}
