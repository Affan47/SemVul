set_name_field (NemoPropertiesWindow *window,
		const gchar *original_name,
		const gchar *name)
{
	gboolean new_widget;
	gboolean use_label;


	use_label = is_multi_file_window (window) || !nemo_file_can_rename (get_original_file (window));
	new_widget = !window->details->name_field || (use_label ? NEMO_IS_ENTRY (window->details->name_field) : GTK_IS_LABEL (window->details->name_field));

	if (new_widget) {
		if (window->details->name_field) {
			gtk_widget_destroy (window->details->name_field);
		}

		if (use_label) {
			window->details->name_field = GTK_WIDGET
				(attach_ellipsizing_value_label (window->details->basic_grid,
								 GTK_WIDGET (window->details->name_label),
								 name));
		} else {
			window->details->name_field = nemo_entry_new ();
			gtk_entry_set_text (GTK_ENTRY (window->details->name_field), name);
			gtk_widget_show (window->details->name_field);

			gtk_grid_attach_next_to (window->details->basic_grid, window->details->name_field,
						 GTK_WIDGET (window->details->name_label),
						 GTK_POS_RIGHT, 1, 1);
			gtk_label_set_mnemonic_widget (GTK_LABEL (window->details->name_label), window->details->name_field);


#ifdef UNDO_ENABLED

			nemo_undo_set_up_nemo_entry_for_undo ( NEMO_ENTRY (window->details->name_field));
			nemo_undo_editable_set_undo_key (GTK_EDITABLE (window->details->name_field), TRUE);
#endif

			g_signal_connect_object (window->details->name_field, "focus_out_event",
						 G_CALLBACK (name_field_focus_out), window, 0);
			g_signal_connect_object (window->details->name_field, "activate",
						 G_CALLBACK (name_field_activate), window, 0);
		}

		gtk_widget_show (window->details->name_field);
	}

	else if (original_name == NULL || strcmp (original_name, name) != 0) {

		if (use_label) {
			gtk_label_set_text (GTK_LABEL (window->details->name_field), name);
		} else {


			gchar *displayed_name = gtk_editable_get_chars (GTK_EDITABLE (window->details->name_field), 0, -1);
			if (strcmp (displayed_name, name) != 0) {
				gtk_entry_set_text (GTK_ENTRY (window->details->name_field), name);
			}
			g_free (displayed_name);
		}
	}
}
