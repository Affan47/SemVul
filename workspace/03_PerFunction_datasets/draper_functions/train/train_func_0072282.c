average_tool_sma_cb (GtkToggleButton *togglebutton, gpointer user_data)
{
	AverageToolState *state = (AverageToolState *)user_data;

	if (!gtk_toggle_button_get_active (togglebutton))
		return;

	gtk_widget_set_sensitive (state->prior_button, TRUE);
	gtk_widget_set_sensitive (state->central_button, TRUE);
	gtk_widget_set_sensitive (state->offset_button, TRUE);
	gtk_widget_set_sensitive (state->interval_entry, TRUE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (state->prior_button), TRUE);
	average_tool_update_sensitivity_cb (NULL, state);
}
