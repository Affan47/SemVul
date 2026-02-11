glatex_insert_usepackage_dialog(G_GNUC_UNUSED GtkMenuItem * menuitem,
									 G_GNUC_UNUSED gpointer gdata)
{
	GtkWidget *dialog = NULL;
	GtkWidget *vbox = NULL;
	GtkWidget *label = NULL;
	GtkWidget *textbox = NULL;
	GtkWidget *table = NULL;
	GtkWidget *label_options = NULL;
	GtkWidget *textbox_options = NULL;

	dialog = gtk_dialog_new_with_buttons(_("Add additional package"),
						 GTK_WINDOW(geany->main_widgets->window),
						 GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_CANCEL,
						 GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
						 NULL);
	vbox = ui_dialog_vbox_new(GTK_DIALOG(dialog));
	gtk_widget_set_name(dialog, "GeanyDialog");
	gtk_box_set_spacing(GTK_BOX(vbox), 10);

	table = gtk_table_new(1, 2, FALSE);
	gtk_table_set_col_spacings(GTK_TABLE(table), 6);
	gtk_table_set_row_spacings(GTK_TABLE(table), 6);

	label = gtk_label_new(_("Package name:"));
	textbox = gtk_entry_new();

	label_options = gtk_label_new(_("Package options:"));
	textbox_options = gtk_entry_new();

	gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
	gtk_misc_set_alignment(GTK_MISC(label_options), 0, 0.5);

	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), textbox, 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), label_options, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), textbox_options, 1, 2, 1, 2);

	gtk_container_add(GTK_CONTAINER(vbox), table);

	g_signal_connect(G_OBJECT(textbox), "activate",
		G_CALLBACK(glatex_enter_key_pressed_in_entry), dialog);
	g_signal_connect(G_OBJECT(textbox_options), "activate",
		G_CALLBACK(glatex_enter_key_pressed_in_entry), dialog);

	gtk_widget_show_all(vbox);

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		const gchar *pkg = NULL;
		const gchar *option = NULL;
		pkg = gtk_entry_get_text(GTK_ENTRY(textbox));
		option = gtk_entry_get_text(GTK_ENTRY(textbox_options));
		glatex_usepackage(pkg, option);
	}

	gtk_widget_destroy(dialog);

}
