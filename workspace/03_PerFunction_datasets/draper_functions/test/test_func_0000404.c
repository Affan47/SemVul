handle_radio_buttons(GtkWidget *owner, StashPref *entry,
		PrefAction action)
{
	EnumWidget *field = entry->extra.radio_buttons;
	gsize count = 0;
	GtkWidget *widget = NULL;

	while (1)
	{
		widget = get_widget(owner, field->widget_id);

		if (!widget)
			continue;

		count++;
		handle_radio_button(widget, field->enum_id, entry->setting, action);
		field++;
		if (!field->widget_id)
			break;
	}
	if (g_slist_length(gtk_radio_button_get_group(GTK_RADIO_BUTTON(widget))) != count)
		g_warning("Missing/invalid radio button widget IDs found!");
}
