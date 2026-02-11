average_tool_interval_cb (G_GNUC_UNUSED GtkWidget *dummy, AverageToolState *state)
{
	int interval;
	int err;

	err = entry_to_int (GTK_ENTRY (state->interval_entry), &interval, TRUE);

	if (err == 0)
		gtk_spin_button_set_range (GTK_SPIN_BUTTON (state->offset_spin),
					   0, interval - 1);
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (state->central_button)))
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (state->offset_spin), interval/2);
}
