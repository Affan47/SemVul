serverinformation_show_popup(void)
{
	GtkWidget *dialog = NULL;
	if (serverstats_sw)
	{
		GtkWidget *win = gtk_widget_get_parent(serverstats_sw);
		if (win)
		{
			gtk_window_present(GTK_WINDOW(win));
			return;
		}
	}

	dialog = gtk_dialog_new_with_buttons(_("Server Information"),
										 GTK_WINDOW(playlist3_get_window()),
										 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										 GTK_STOCK_CLOSE, GTK_RESPONSE_OK, NULL);

	serverstats_selected(GTK_DIALOG(dialog)->vbox);

	gtk_window_resize(GTK_WINDOW(dialog),
					  cfg_get_single_value_as_int_with_default(config, "serverstats", "dialog-width", 400),
					  cfg_get_single_value_as_int_with_default(config, "serverstats", "dialog-height", 400));

	g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(serverinformation_popup_close), NULL);
	gtk_widget_show(dialog);

}
