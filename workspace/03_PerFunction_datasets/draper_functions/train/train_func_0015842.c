on_selectkb_cancel_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

	if (GUI_main_window() == NULL)
	{
		gtk_main_quit();
		gtk_exit (0);
	}

	gtk_widget_destroy ((gtk_widget_get_toplevel(GTK_WIDGET(button))));
}
