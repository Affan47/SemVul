cer_init(MainInfo *min, gchar **name)
{
	P_Errors	*page = &the_page;
	GtkWidget	*vbox, *frame;

	if(name == NULL)
		return NULL;

	*name = _("Errors");

	page->min = min;
	page->modified = FALSE;

	page->vbox = gtk_vbox_new(FALSE, 0);

	frame = gtk_frame_new(_("Error and Status Message Display"));
	vbox = gtk_vbox_new(FALSE, 0);
	page->standard = gtk_radio_button_new_with_label(NULL, _("Status Bar, Above Panes"));
	g_signal_connect(G_OBJECT(page->standard), "toggled", G_CALLBACK(evt_dialog_toggled), page);
	gtk_box_pack_start(GTK_BOX(vbox), page->standard, FALSE, FALSE, 0);
	page->main_title = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(page->standard)), _("Main Window's Title Bar"));
	g_signal_connect(G_OBJECT(page->main_title), "toggled", G_CALLBACK(evt_dialog_toggled), page);
	gtk_box_pack_start(GTK_BOX(vbox), page->main_title, FALSE, FALSE, 0);
	page->dialog = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(page->standard)), _("Separate Dialog"));
	g_signal_connect(G_OBJECT(page->dialog), "toggled", G_CALLBACK(evt_dialog_toggled), page);
	gtk_box_pack_start(GTK_BOX(vbox), page->dialog, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), vbox);
	gtk_box_pack_start(GTK_BOX(page->vbox), frame, FALSE, FALSE, 0);

	page->beep = gtk_check_button_new_with_label(_("Cause Console Beep on Error?"));
	g_signal_connect(G_OBJECT(page->beep), "toggled", G_CALLBACK(evt_beep_toggled), page);
	gtk_box_pack_start(GTK_BOX(page->vbox), page->beep, FALSE, FALSE, 0);

	gtk_widget_show_all(page->vbox);
	return page->vbox;
}
