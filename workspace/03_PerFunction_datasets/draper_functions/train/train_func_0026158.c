CreateInCallDialog(void)
{
	GtkWidget *button, *hbox;

	inCallDialog.dialog = gtk_dialog_new();
	gtk_window_position(GTK_WINDOW(inCallDialog.dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_title(GTK_WINDOW(inCallDialog.dialog), _("Call in progress"));
	gtk_container_set_border_width(GTK_CONTAINER(inCallDialog.dialog), 5);
	gtk_signal_connect(GTK_OBJECT(inCallDialog.dialog), "delete_event",
			   GTK_SIGNAL_FUNC(DeleteEvent), NULL);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(inCallDialog.dialog)->vbox), hbox, FALSE, FALSE, 5);
	gtk_widget_show(hbox);

	inCallDialog.label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(hbox), inCallDialog.label, FALSE, FALSE, 0);
	gtk_widget_show(inCallDialog.label);

	button = gtk_button_new_with_label(_("Hide"));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(inCallDialog.dialog)->action_area),
			   button, TRUE, FALSE, 0);
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			   GTK_SIGNAL_FUNC(HideCallDialog), (gpointer) inCallDialog.dialog);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_grab_default(button);
	gtk_widget_show(button);
}
