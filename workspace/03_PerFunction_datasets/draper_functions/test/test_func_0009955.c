gfire_game_manager_update_executable_toggled_cb(GtkBuilder *p_builder, GtkWidget *p_executable_check_button)
{
	if (!p_builder)
	{
		purple_debug_error("gfire", "Couldn't access game manager interface.");
		return;
	}

	GtkWidget *add_executable_check_button = GTK_WIDGET(gtk_builder_get_object(p_builder, "add_executable_check_button"));
	GtkWidget *add_launch_button = GTK_WIDGET(gtk_builder_get_object(p_builder, "add_launch_button"));
	GtkWidget *edit_executable_check_button = GTK_WIDGET(gtk_builder_get_object(p_builder, "edit_executable_check_button"));
	GtkWidget *edit_launch_button = GTK_WIDGET(gtk_builder_get_object(p_builder, "edit_launch_button"));

	gboolean check_button_state;
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(add_executable_check_button)))
		check_button_state = FALSE;
	else
		check_button_state = TRUE;

	gtk_widget_set_sensitive(add_launch_button, check_button_state);

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(edit_executable_check_button)))
		check_button_state = FALSE;
	else
		check_button_state = TRUE;

	gtk_widget_set_sensitive(edit_launch_button, check_button_state);
}
