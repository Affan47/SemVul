ca_changepwd_pwd_protect_radiobutton_toggled (GtkWidget *button, gpointer user_data)
{
	GtkBuilder * dialog_gtkb;
	GObject * widget = NULL;


	if (! G_IS_OBJECT(button))
		return TRUE;

	dialog_gtkb = g_object_get_data (G_OBJECT(button), "dialog_gtkb");
	if (! dialog_gtkb)
		return TRUE;

	widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_pwd_protect_yes_radiobutton");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) {


		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_label2");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), TRUE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_label3");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), TRUE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_newpwd_entry1");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), TRUE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_newpwd_entry2");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), TRUE);

		ca_changepwd_newpwd_entry_changed (button, NULL);

	} else {

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_label2");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), FALSE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_label3");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), FALSE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_newpwd_entry1");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), FALSE);

		widget = gtk_builder_get_object (dialog_gtkb, "ca_changepwd_newpwd_entry2");
		gtk_widget_set_sensitive (GTK_WIDGET(widget), FALSE);
	}

	return FALSE;
}
