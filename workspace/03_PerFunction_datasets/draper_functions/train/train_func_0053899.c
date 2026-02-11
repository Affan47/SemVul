_e2p_find_create_toggle_button_real (GtkWidget *box,
	findflag_t f, gboolean state, gchar *label, gpointer callback,
	E2_FindDialogRuntime *rt)
{
	gboolean first;
	if (nocacheflags)
	{
		first = state;

		if (state)
			_e2p_find_set_flag (f, TRUE);
	}
	else
		first = _e2p_find_get_flag (f);

	GtkWidget *button = e2_button_add_toggle (box, TRUE, first,
		label, NULL, TRUE, E2_PADDING, callback, (gpointer) f);
	g_object_set_data (G_OBJECT (button), "reset_yourself",
		state ? _e2p_find_set_toggle_button_on : _e2p_find_set_toggle_button_off );
	return button;
}
