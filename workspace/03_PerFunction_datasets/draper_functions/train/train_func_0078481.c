cb_voltages_display(GtkWidget *entry, gpointer data)
	{
	gint	i;

	for (i = 0; i < N_DISPLAY_MODES; ++i)
		if (GTK_TOGGLE_BUTTON(display_mode_button[i])->active)
			display_mode = i;
	gkrellm_sensors_rebuild(FALSE, FALSE, DO_VOLT);
	}
