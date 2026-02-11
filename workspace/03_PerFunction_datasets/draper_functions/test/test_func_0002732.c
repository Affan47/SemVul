cache_manager_render_dialog(GtkWidget *widget, const gchar *path)
{
	CleanData *cd;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *button;

	cd = g_new0(CleanData, 1);

	cd->gd = generic_dialog_new(_("Create thumbnails"),
				    "create_thumbnails",
				    widget, FALSE,
				    NULL, cd);
	gtk_window_set_default_size(GTK_WINDOW(cd->gd->dialog), PURGE_DIALOG_WIDTH, -1);
	cd->gd->cancel_cb = cache_manager_render_close_cb;
	cd->button_close = generic_dialog_add_button(cd->gd, GTK_STOCK_CLOSE, NULL,
						     cache_manager_render_close_cb, FALSE);
	cd->button_start = generic_dialog_add_button(cd->gd, GTK_STOCK_OK, _("S_tart"),
						     cache_manager_render_start_cb, FALSE);
	cd->button_stop = generic_dialog_add_button(cd->gd, GTK_STOCK_STOP, NULL,
						    cache_manager_render_stop_cb, FALSE);
	gtk_widget_set_sensitive(cd->button_stop, FALSE);

	generic_dialog_add_message(cd->gd, NULL, _("Create thumbnails"), NULL);

	hbox = pref_box_new(cd->gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, 0);
	pref_spacer(hbox, PREF_PAD_INDENT);
	cd->group = pref_box_new(hbox, TRUE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);

	hbox = pref_box_new(cd->group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	pref_label_new(hbox, _("Folder:"));

	label = tab_completion_new(&cd->entry, path, NULL, NULL);
	tab_completion_add_select_button(cd->entry,_("Select folder") , TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	pref_checkbox_new_int(cd->group, _("Include subfolders"), FALSE, &cd->recurse);
	button = pref_checkbox_new_int(cd->group, _("Store thumbnails local to source images"), FALSE, &cd->local);
	gtk_widget_set_sensitive(button, options->thumbnails.spec_standard);

	pref_line(cd->gd->vbox, PREF_PAD_SPACE);
	hbox = pref_box_new(cd->gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);

	cd->progress = gtk_entry_new();
	GTK_WIDGET_UNSET_FLAGS(cd->progress, GTK_CAN_FOCUS);
	gtk_editable_set_editable(GTK_EDITABLE(cd->progress), FALSE);
	gtk_entry_set_text(GTK_ENTRY(cd->progress), _("click start to begin"));
	gtk_box_pack_start(GTK_BOX(hbox), cd->progress, TRUE, TRUE, 0);
	gtk_widget_show(cd->progress);

	cd->spinner = spinner_new(NULL, -1);
	gtk_box_pack_start(GTK_BOX(hbox), cd->spinner, FALSE, FALSE, 0);
	gtk_widget_show(cd->spinner);

	cd->list = NULL;

	gtk_widget_show(cd->gd->dialog);
}
