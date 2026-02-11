add_edit_dialog_create (charpick_data *curr_data, gchar *string, gchar *title)
{
	GtkWidget *dialog;
	GtkWidget *entry;
	GtkWidget *dbox;
	GtkWidget *vbox, *hbox;
	GtkWidget *label;

	dialog = gtk_dialog_new_with_buttons (_(title), GTK_WINDOW (curr_data->propwindow),
							    GTK_DIALOG_DESTROY_WITH_PARENT,
							    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							    GTK_STOCK_OK, GTK_RESPONSE_OK,
							    NULL);

	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (curr_data->propwindow));
	gtk_widget_set_sensitive (curr_data->propwindow, FALSE);

	gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_OK);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
	gtk_box_set_spacing (GTK_BOX (gtk_dialog_get_content_area(GTK_DIALOG (dialog))), 2);

	dbox = gtk_dialog_get_content_area(GTK_DIALOG (dialog));

	vbox = gtk_vbox_new (FALSE, 12);
	gtk_box_pack_start (GTK_BOX (dbox), vbox, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);

	hbox = gtk_hbox_new (FALSE, 12);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

	label = gtk_label_new_with_mnemonic (_("_Palette:"));
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry = gtk_entry_new ();
	gtk_label_set_mnemonic_widget (GTK_LABEL (label), entry);
	 gtk_entry_set_activates_default (GTK_ENTRY (entry), TRUE);
	gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);

	set_access_namedesc (entry, _("Palette entry"),
				         _("Modify a palette by adding or removing characters"));
	if (string)
		gtk_entry_set_text (GTK_ENTRY (entry), string);

	curr_data->add_edit_dialog = dialog;
	curr_data->add_edit_entry = entry;
}
