settings_window_set_bool (GtkToggleButton *button)
{
	START_FUNC
#ifdef ENABLE_RAMBLE
	if ((!strcmp(gtk_buildable_get_name(GTK_BUILDABLE(button)), "ramble_distance")) ||
		(!strcmp(gtk_buildable_get_name(GTK_BUILDABLE(button)), "ramble_time"))) {
		if (!strcmp(gtk_buildable_get_name(GTK_BUILDABLE(button)), "ramble_distance") &&
			gtk_toggle_button_get_active(button)) {
			settings_set_string(SETTINGS_RAMBLE_ALGO, "distance");
			gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_threshold1")));
			gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_threshold2")));
			gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_timer")));
		} else {
			settings_set_string(SETTINGS_RAMBLE_ALGO, "time");
			gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_threshold1")));
			gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_threshold2")));
			gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
				"ramble_timer")));
		}
	} else {
#endif
	settings_set_bool(settings_get_settings_name(GTK_WIDGET(button)),
		gtk_toggle_button_get_active(button));
	if (!strcmp(gtk_buildable_get_name(GTK_BUILDABLE(button)), "flo_auto_hide")) {
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
			"flo_move_to_widget")), gtk_toggle_button_get_active(button));
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
			"flo_intermediate_icon")), gtk_toggle_button_get_active(button));
	} else if (!strcmp(gtk_buildable_get_name(GTK_BUILDABLE(button)), "flo_system_font")) {
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
			"flo_font_label")), !gtk_toggle_button_get_active(button));
		gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(settings_window->gtkbuilder,
			"flo_font")), !gtk_toggle_button_get_active(button));
	}
#ifdef ENABLE_RAMBLE
	}
#endif
	END_FUNC
}
