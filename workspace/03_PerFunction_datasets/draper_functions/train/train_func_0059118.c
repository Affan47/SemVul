gyrus_dialog_find_mailbox_init (GyrusDialogFindMailbox *dialog)
{
	GtkListStore *model;

	dialog->priv = g_new0 (GyrusDialogFindMailboxPrivate, 1);

	dialog->priv->admin = NULL;

	gtk_window_set_title (GTK_WINDOW (dialog), _("Find mailbox"));
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);

	gyrus_dialog_find_mailbox_init_get_widgets (dialog);
	gyrus_dialog_find_mailbox_init_connect_signals (dialog);

	model = gtk_list_store_new (1, G_TYPE_STRING);

	gtk_combo_box_set_model (GTK_COMBO_BOX (dialog->priv->comboboxentry_mailbox),
				 GTK_TREE_MODEL (model));
	gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (dialog->priv->comboboxentry_mailbox),
					     0);


	gtk_widget_set_can_default (dialog->priv->button_find, TRUE);
	gtk_widget_grab_default (dialog->priv->button_find);

	gtk_widget_set_sensitive (dialog->priv->button_find, FALSE);
	gtk_widget_show_all (GTK_WIDGET (dialog));
}
