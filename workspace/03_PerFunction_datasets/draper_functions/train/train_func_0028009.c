CreateSaveQuestionDialog(GtkSignalFunc SaveFunc, GtkSignalFunc DontSaveFunc)
{
	GtkWidget *dialog;
	GtkWidget *button, *label, *hbox, *pixmap;

	dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), _("Save changes?"));
	gtk_window_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_signal_connect(GTK_OBJECT(dialog), "delete_event", GTK_SIGNAL_FUNC(DeleteEvent), NULL);

	button = gtk_button_new_with_label(_("Save"));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, TRUE, TRUE, 10);
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			   GTK_SIGNAL_FUNC(SaveFunc), (gpointer) dialog);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_grab_default(button);
	gtk_widget_show(button);

	button = gtk_button_new_with_label(_("Don't save"));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, TRUE, TRUE, 10);
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			   GTK_SIGNAL_FUNC(DontSaveFunc), (gpointer) dialog);
	gtk_widget_show(button);

	button = gtk_button_new_with_label(_("Cancel"));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, TRUE, TRUE, 10);
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			   GTK_SIGNAL_FUNC(CancelDialog), (gpointer) dialog);
	gtk_widget_show(button);

	gtk_container_set_border_width(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), hbox);
	gtk_widget_show(hbox);

	pixmap = gtk_pixmap_new(questMark.pixmap, questMark.mask);
	gtk_box_pack_start(GTK_BOX(hbox), pixmap, FALSE, FALSE, 10);
	gtk_widget_show(pixmap);

	label = gtk_label_new(_("You have made changes in your\ncontacts directory.\n\
\n\nDo you want to save these changes into your phone?\n"));
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 2);
	gtk_widget_show(label);

	return dialog;
}
