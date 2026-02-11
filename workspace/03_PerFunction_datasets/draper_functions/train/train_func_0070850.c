launcher_properties (Launcher  *launcher)
{
	if (launcher->prop_dialog != NULL) {
		gtk_window_set_screen (GTK_WINDOW (launcher->prop_dialog),
				       gtk_widget_get_screen (launcher->button));
		gtk_window_present (GTK_WINDOW (launcher->prop_dialog));
		return;
	}

	launcher->prop_dialog = panel_ditem_editor_new (NULL,
							launcher->key_file,
							launcher->location,
							_("Launcher Properties"));

	panel_widget_register_open_dialog (PANEL_WIDGET
					   (gtk_widget_get_parent (launcher->info->widget)),
					   launcher->prop_dialog);

	panel_ditem_register_save_uri_func (PANEL_DITEM_EDITOR (launcher->prop_dialog),
					    launcher_save_uri,
					    launcher);

	g_signal_connect (launcher->prop_dialog, "changed",
			  G_CALLBACK (launcher_changed), launcher);

	g_signal_connect (launcher->prop_dialog, "command_changed",
			  G_CALLBACK (launcher_command_changed), launcher);

	g_signal_connect (launcher->prop_dialog, "saved",
			  G_CALLBACK (launcher_saved), launcher);

	g_signal_connect (launcher->prop_dialog, "error_reported",
			  G_CALLBACK (launcher_error_reported), NULL);

	g_signal_connect (launcher->prop_dialog, "destroy",
			  G_CALLBACK (gtk_widget_destroyed),
			  &launcher->prop_dialog);

	gtk_widget_show (launcher->prop_dialog);
}
