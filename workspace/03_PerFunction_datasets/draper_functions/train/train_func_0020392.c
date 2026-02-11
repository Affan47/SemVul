ianjuta_msgman_add_view (IAnjutaMessageManager *plugin,
						 const gchar *file, const gchar *icon,
						 GError **e)
{
	MessageView* message_view;
	AnjutaShell* shell = ANJUTA_PLUGIN(plugin)->shell;
	GtkWidget *msgman = ANJUTA_PLUGIN_MESSAGE_VIEW (plugin)->msgman;
	if (ANJUTA_PLUGIN_MESSAGE_VIEW (plugin)->widget_shown == FALSE)
	{
		GtkWidget* hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		GtkWidget* label = gtk_label_new (_("Messages"));
		GtkWidget* image = gtk_image_new_from_stock ("message-manager-plugin-icon",
		                                            GTK_ICON_SIZE_MENU);
		gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX(hbox), anjuta_msgman_get_tabber (ANJUTA_MSGMAN(msgman)),
		                    TRUE, TRUE, 5);

		gtk_widget_show_all (hbox);

		create_toggle_buttons (ANJUTA_PLUGIN_MESSAGE_VIEW(plugin), hbox);

		gtk_widget_show_all (msgman);
		anjuta_shell_add_widget_custom (shell, msgman,
							 "AnjutaMessageView", _("Messages"),
							 "message-manager-plugin-icon", hbox,
							 ANJUTA_SHELL_PLACEMENT_BOTTOM, NULL);
		ANJUTA_PLUGIN_MESSAGE_VIEW (plugin)->widget_shown = TRUE;
	}
	anjuta_shell_present_widget(shell, msgman, NULL);
	message_view = anjuta_msgman_add_view (ANJUTA_MSGMAN (msgman), file, icon);
	return IANJUTA_MESSAGE_VIEW (message_view);
}
