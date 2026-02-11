set_auth_sensitivity(struct VcalendarPage *page)
{
	const gchar *export_path, *export_freebusy_path;
	gboolean export_enable, export_freebusy_enable;

	export_enable = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(page->export_enable_btn));
	export_freebusy_enable = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(page->export_freebusy_enable_btn));

	export_path = gtk_entry_get_text(GTK_ENTRY(page->export_path_entry));
	export_freebusy_path = gtk_entry_get_text(GTK_ENTRY(page->export_freebusy_path_entry));
	if (export_enable && export_path &&
	    (!strncmp(export_path, "http://", 7) ||
	     !strncmp(export_path, "ftp://", 6) ||
	     !strncmp(export_path, "https://", 8) ||
	     !strncmp(export_path, "sftp://", 5) ||
	     !strncmp(export_path, "webcal://", 9) ||
	     !strncmp(export_path, "webcals://", 10))) {
		gtk_widget_set_sensitive(page->export_user_label, TRUE);
		gtk_widget_set_sensitive(page->export_user_entry, TRUE);
		gtk_widget_set_sensitive(page->export_pass_label, TRUE);
		gtk_widget_set_sensitive(page->export_pass_entry, TRUE);
	} else {
		gtk_widget_set_sensitive(page->export_user_label, FALSE);
		gtk_widget_set_sensitive(page->export_user_entry, FALSE);
		gtk_widget_set_sensitive(page->export_pass_label, FALSE);
		gtk_widget_set_sensitive(page->export_pass_entry, FALSE);
	}
	if (export_freebusy_enable && export_freebusy_path &&
	    (!strncmp(export_freebusy_path, "http://", 7) ||
	     !strncmp(export_freebusy_path, "ftp://", 6) ||
	     !strncmp(export_freebusy_path, "https://", 8) ||
	     !strncmp(export_freebusy_path, "sftp://", 5) ||
	     !strncmp(export_freebusy_path, "webcal://", 9) ||
	     !strncmp(export_freebusy_path, "webcals://", 10))) {
		gtk_widget_set_sensitive(page->export_freebusy_user_label, TRUE);
		gtk_widget_set_sensitive(page->export_freebusy_user_entry, TRUE);
		gtk_widget_set_sensitive(page->export_freebusy_pass_label, TRUE);
		gtk_widget_set_sensitive(page->export_freebusy_pass_entry, TRUE);
	} else {
		gtk_widget_set_sensitive(page->export_freebusy_user_label, FALSE);
		gtk_widget_set_sensitive(page->export_freebusy_user_entry, FALSE);
		gtk_widget_set_sensitive(page->export_freebusy_pass_label, FALSE);
		gtk_widget_set_sensitive(page->export_freebusy_pass_entry, FALSE);
	}
}
