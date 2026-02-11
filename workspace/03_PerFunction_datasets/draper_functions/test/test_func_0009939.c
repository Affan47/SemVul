gtkut_check_button(GtkWidget *inParentBox, const char *inButtonText,
	int inIsSelected, GCallback inSignalFunc, void *inCallbackData)
{
	GtkWidget *button = NULL;

	if (inButtonText == NULL)
		button = gtk_check_button_new();
	else
		button = gtk_check_button_new_with_mnemonic(inButtonText);

	gtk_widget_show(button);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), inIsSelected);

	gtk_box_pack_start(GTK_BOX(inParentBox), button, FALSE, FALSE, 0);

	g_signal_connect(GTK_OBJECT(button), "clicked", inSignalFunc,
		inCallbackData);

	return (button);
}
