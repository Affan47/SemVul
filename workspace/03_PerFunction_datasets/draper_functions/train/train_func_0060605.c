add_find_checkboxes(GtkDialog *dialog)
{
	GtkWidget *checkbox1, *checkbox2, *check_regexp, *check_back, *checkbox5,
			  *checkbox7, *hbox, *fbox, *mbox;

	check_regexp = gtk_check_button_new_with_mnemonic(_("_Use regular expressions"));
	ui_hookup_widget(dialog, check_regexp, "check_regexp");
	gtk_button_set_focus_on_click(GTK_BUTTON(check_regexp), FALSE);
	gtk_widget_set_tooltip_text(check_regexp, _("Use POSIX-like regular expressions. "
		"For detailed information about using regular expressions, please read the documentation."));
	g_signal_connect(check_regexp, "toggled",
		G_CALLBACK(on_find_replace_checkbutton_toggled), dialog);

	if (dialog != GTK_DIALOG(find_dlg.dialog))
	{
		check_back = gtk_check_button_new_with_mnemonic(_("Search _backwards"));
		ui_hookup_widget(dialog, check_back, "check_back");
		gtk_button_set_focus_on_click(GTK_BUTTON(check_back), FALSE);
	}
	else
	{
		GtkSizeGroup *label_size;
		check_back = gtk_label_new(NULL);
		label_size = gtk_size_group_new(GTK_SIZE_GROUP_VERTICAL);
		gtk_size_group_add_widget(GTK_SIZE_GROUP(label_size), check_back);
		gtk_size_group_add_widget(GTK_SIZE_GROUP(label_size), check_regexp);
		g_object_unref(label_size);
	}
	checkbox7 = gtk_check_button_new_with_mnemonic(_("Use _escape sequences"));
	ui_hookup_widget(dialog, checkbox7, "check_escape");
	gtk_button_set_focus_on_click(GTK_BUTTON(checkbox7), FALSE);
	gtk_widget_set_tooltip_text(checkbox7,
		_("Replace \\\\, \\t, \\n, \\r and \\uXXXX (Unicode chararacters) with the "
		  "corresponding control characters"));


	fbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(fbox), check_regexp);
	gtk_container_add(GTK_CONTAINER(fbox), checkbox7);
	gtk_container_add(GTK_CONTAINER(fbox), check_back);

	checkbox1 = gtk_check_button_new_with_mnemonic(_("C_ase sensitive"));
	ui_hookup_widget(dialog, checkbox1, "check_case");
	gtk_button_set_focus_on_click(GTK_BUTTON(checkbox1), FALSE);

	checkbox2 = gtk_check_button_new_with_mnemonic(_("Match only a _whole word"));
	ui_hookup_widget(dialog, checkbox2, "check_word");
	gtk_button_set_focus_on_click(GTK_BUTTON(checkbox2), FALSE);

	checkbox5 = gtk_check_button_new_with_mnemonic(_("Match from s_tart of word"));
	ui_hookup_widget(dialog, checkbox5, "check_wordstart");
	gtk_button_set_focus_on_click(GTK_BUTTON(checkbox5), FALSE);


	mbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(mbox), checkbox1);
	gtk_container_add(GTK_CONTAINER(mbox), checkbox2);
	gtk_container_add(GTK_CONTAINER(mbox), checkbox5);

	hbox = gtk_hbox_new(TRUE, 6);
	gtk_container_add(GTK_CONTAINER(hbox), fbox);
	gtk_container_add(GTK_CONTAINER(hbox), mbox);
	return hbox;
}
