cb_combo_custom_activate (GOPalette *palette, GOSelector *selector)
{
	GtkWidget *color_dialog;
	GtkWidget *color_selection;
	GdkRGBA gdk_color;
	GOColor color;
	GOColorSelectorState *state = go_selector_get_user_data (selector);

	color_dialog = g_object_get_data (G_OBJECT (selector), "color-dialog");
	if (color_dialog != NULL) {
		color_selection = gtk_color_selection_dialog_get_color_selection (GTK_COLOR_SELECTION_DIALOG (color_dialog));
		color = go_color_selector_get_color (selector, NULL);
		gtk_color_selection_set_current_rgba (GTK_COLOR_SELECTION (color_selection),
						       go_color_to_gdk_rgba (color, &gdk_color));
		gtk_window_present (GTK_WINDOW (color_dialog));
		return;
	}

	color_dialog = gtk_color_selection_dialog_new (_("Custom color..."));
	color_selection = gtk_color_selection_dialog_get_color_selection (GTK_COLOR_SELECTION_DIALOG (color_dialog));
	gtk_color_selection_set_has_opacity_control (GTK_COLOR_SELECTION (color_selection), state->allow_alpha);
	g_object_set_data_full (G_OBJECT (selector), "color-dialog", color_dialog,
				(GDestroyNotify) gtk_widget_destroy);
	color = go_color_selector_get_color (selector, NULL);
	gtk_color_selection_set_current_rgba (GTK_COLOR_SELECTION (color_selection),
					       go_color_to_gdk_rgba (color, &gdk_color));
	if (state->allow_alpha)
		gtk_color_selection_set_current_alpha (GTK_COLOR_SELECTION (color_selection),
					       GO_COLOR_UINT_A (color) * 257);
	g_signal_connect (color_dialog, "response", G_CALLBACK (cb_color_dialog_response), selector);
       	gtk_widget_show (color_dialog);
}
