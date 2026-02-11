check_tab_accelerators(const GtkWidget *inWidget,
	const chat_window *inCW, GdkModifierType inModifiers,
	const GdkEventKey *inEvent)
{
	if (inCW->notebook) {
		GdkDeviceKey accel_prev_tab, accel_next_tab;

		gtk_accelerator_parse(cGetLocalPref("accel_next_tab"),
			&(accel_next_tab.keyval), &(accel_next_tab.modifiers));

		gtk_accelerator_parse(cGetLocalPref("accel_prev_tab"),
			&(accel_prev_tab.keyval), &(accel_prev_tab.modifiers));


		if (inModifiers == accel_prev_tab.modifiers
			&& inEvent->keyval == accel_prev_tab.keyval) {

			g_signal_stop_emission_by_name(G_OBJECT(inWidget),
				"key-press-event");
			gtk_notebook_prev_page(GTK_NOTEBOOK(inCW->notebook));
			return TRUE;
		} else if (inModifiers == accel_next_tab.modifiers
			&& inEvent->keyval == accel_next_tab.keyval) {

			g_signal_stop_emission_by_name(G_OBJECT(inWidget),
				"key-press-event");
			gtk_notebook_next_page(GTK_NOTEBOOK(inCW->notebook));
			return TRUE;
		}
	}

	return FALSE;
}
