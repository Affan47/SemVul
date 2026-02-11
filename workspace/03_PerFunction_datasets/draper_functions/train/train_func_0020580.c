on_special_action_radiobutton_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

	if ( gtk_toggle_button_get_active(togglebutton) == TRUE )
	{
		handle_changed_special_action (
		           GTK_WIDGET (togglebutton),
		           GTK_ENTRY (lookup_widget( GTK_WIDGET(togglebutton), "plugin_comboentry" )),
		           GTK_ENTRY (lookup_widget( GTK_WIDGET(togglebutton), "plugin_function_comboentry" )) );
	}
}
