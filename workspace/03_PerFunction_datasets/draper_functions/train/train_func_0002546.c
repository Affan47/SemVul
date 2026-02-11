show_std_properties(void)
{
	GtkWidget *dialog = GTK_WIDGET (gtk_builder_get_object (gxml, "action_prefs_dialog"));
	GtkWidget *lock_monitor_radio = GTK_WIDGET (gtk_builder_get_object (gxml, "radiobutton7"));
	GtkWidget *turn_off_radio = GTK_WIDGET (gtk_builder_get_object (gxml, "radiobutton8"));

	gboolean first_selected = g_key_file_get_boolean(current_key, untitled_name, "ActionFirstSelected", NULL);

	if (first_selected)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lock_monitor_radio), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(turn_off_radio), TRUE);
	}

	gtk_dialog_run(GTK_DIALOG(dialog));

	first_selected = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lock_monitor_radio));

	g_key_file_set_boolean(current_key, untitled_name, "ActionFirstSelected", first_selected);

	gtk_widget_hide(GTK_WIDGET(dialog));
}
