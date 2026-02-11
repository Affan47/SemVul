select_diff_dialog_run(toplevel_t * top)
{
	GladeXML *xml = glade_xml_new(toplevel_get_glade_xml(top), "select_components", NULL);
	GtkDialog *dialog = GTK_DIALOG(glade_xml_get_widget(xml, "select_components"));
	assert(dialog != NULL);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), toplevel_get_window(top));

	size_t i;
	const struct component *c;
	for (i = 0; comps[i].name != NULL; i++) {
		c = comps + i;
		GtkToggleButton *cb = GTK_TOGGLE_BUTTON(glade_xml_get_widget(xml, c->name));
		assert(cb != NULL);
		gtk_toggle_button_set_active(cb, c->bit & prev_selection ? TRUE : FALSE);
	}

	GtkButton *b = GTK_BUTTON(glade_xml_get_widget(xml, "select all button"));
	assert(b != NULL);
	g_signal_connect(b, "clicked", G_CALLBACK(select_diff_on_select_all_click), xml);
	b = GTK_BUTTON(glade_xml_get_widget(xml, "select none button"));
	assert(b != NULL);
	g_signal_connect(b, "clicked", G_CALLBACK(select_diff_on_select_none_click), xml);

	uint32_t result = 0;
	while (result == 0) {
		result = 0;
		if (gtk_dialog_run(dialog) != GTK_RESPONSE_OK) {
			gtk_widget_destroy(GTK_WIDGET(dialog));
			return 0;
		}

		for (i = 0; comps[i].name != NULL; i++) {
			c = comps + i;
			GtkToggleButton *cb = GTK_TOGGLE_BUTTON(glade_xml_get_widget(xml, c->name));
			if (gtk_toggle_button_get_active(cb)) {
				result |= c->bit;
			}
		}

		if (result == 0) {
			toplevel_ERR(top, "%s", "At least one component must be selected.");
		}
	}

	gtk_widget_destroy(GTK_WIDGET(dialog));
	prev_selection = result;
	return result;
}
