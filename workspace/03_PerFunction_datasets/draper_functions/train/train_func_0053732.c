on_set_preferences1_activate (GtkAction * action, AnjutaWindow *win)
{

	GtkWidget *preferences_dialog;

	if (anjuta_preferences_is_dialog_created (win->preferences))
	{
		gtk_window_present (GTK_WINDOW (anjuta_preferences_get_dialog (win->preferences)));
		return;
	}
	preferences_dialog = anjuta_preferences_get_dialog (win->preferences);
	gtk_window_set_title (GTK_WINDOW (preferences_dialog), _("GtkPod Preferences"));


	anjuta_window_install_preferences (win);

	g_signal_connect_swapped (G_OBJECT (preferences_dialog),
					  		  "response",
					  		  G_CALLBACK (gtk_widget_destroy),
					  		  preferences_dialog);

	gtk_window_set_transient_for (GTK_WINDOW (preferences_dialog),
								  GTK_WINDOW (win));

	gtk_widget_show (preferences_dialog);
}
