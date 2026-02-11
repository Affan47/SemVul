edit_person_ok(GtkWidget *widget, gboolean *cancelled) {
	GList *listEMail = edit_person_build_email_list();
	GList *listAttrib = edit_person_build_attrib_list();
	gchar *cn = edit_person_get_common_name_from_widgets();

	if( (cn == NULL || *cn == '\0') && listEMail == NULL && listAttrib == NULL ) {
		gint val;

		val = alertpanel( _("Add New Person"),
#ifndef GENERIC_UMPC
				_("Adding a new person requires at least one of the\n"
				  "following values to be set:\n"
				  " - Display Name\n"
				  " - First Name\n"
				  " - Last Name\n"
				  " - Nickname\n"
				  " - any email address\n"
				  " - any additional attribute\n\n"
				  "Click OK to keep editing this contact.\n"
				  "Click Cancel to close without saving."),
#else
				_("Adding a new person requires at least one of the\n"
				  "following values to be set:\n"
				  " - First Name\n"
				  " - Last Name\n"
				  " - any email address\n"
				  " - any additional attribute\n\n"
				  "Click OK to keep editing this contact.\n"
				  "Click Cancel to close without saving."),
#endif
				GTK_STOCK_CANCEL, "+"GTK_STOCK_OK, NULL );
		if( val == G_ALERTDEFAULT ) {
			edit_person_cancel(widget, cancelled);
		}
		g_free( cn );
		return;
	}
	g_free( cn );

	*cancelled = FALSE;
	if (prefs_common.addressbook_use_editaddress_dialog)
		gtk_main_quit();
	else
		addressbook_edit_person_close( *cancelled );
}
