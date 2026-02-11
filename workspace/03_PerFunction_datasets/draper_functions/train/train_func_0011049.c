PREFERENCES_expert_option_edited  (GtkCellRendererText *cell,
											gchar *path_string,
											gchar *new_text, gpointer data)
	{
		if (data)
			PREFERENCES(data)->expert_set_selected_option (new_text);
		else
			unknown_internal_error ();
	}
