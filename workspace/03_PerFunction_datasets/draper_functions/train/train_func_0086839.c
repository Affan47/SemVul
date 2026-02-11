average_tool_cma_cb (GtkToggleButton *togglebutton, gpointer user_data)
{
	AverageToolState *state = (AverageToolState *)user_data;

	if (!gtk_toggle_button_get_active (togglebutton))
		return;

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (state->prior_button), TRUE);
	gtk_widget_set_sensitive (state->prior_button, FALSE);
	gtk_widget_set_sensitive (state->central_button, FALSE);
	gtk_widget_set_sensitive (state->offset_button, FALSE);
	gtk_widget_set_sensitive (state->interval_entry, FALSE);
	average_tool_update_sensitivity_cb (NULL, state);
}
