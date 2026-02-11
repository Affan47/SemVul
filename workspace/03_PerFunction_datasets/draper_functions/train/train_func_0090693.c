capitalize_check_toggled(GtkWidget * widget, gpointer data) {

	capitalize_gui_t * gui = (capitalize_gui_t *)data;

	gboolean state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->check));
	gtk_widget_set_sensitive(gui->combo, state);
	gtk_widget_set_sensitive(gui->check_pre, state);
	gtk_widget_set_sensitive(gui->check_low, state);

	if (state == FALSE) {
		gtk_widget_set_sensitive(gui->entry_pre, FALSE);
	} else {
		capitalize_check_pre_toggled(widget, data);
	}
}
