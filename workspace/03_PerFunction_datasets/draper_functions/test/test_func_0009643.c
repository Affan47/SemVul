type_view (void)
{

	if (!mailbox_)
		return;

	gtk_widget_set_sensitive (get("browse_address"), true);
	identity_view (false);
	details_view (false);
	auth_view (false);
	certificate_view (false);
	mailbox_view (false);
	delay_view (false);

	guint protocol = mailbox_->protocol ();
	selected_type_ = TYPE_AUTODETECT;

	if ((protocol == PROTOCOL_FILE) || (protocol == PROTOCOL_MH)
		|| (protocol == PROTOCOL_MH_BASIC)
		|| (protocol == PROTOCOL_MH_SYLPHEED)
		|| (protocol == PROTOCOL_MAILDIR)) {
		selected_type_ = TYPE_LOCAL;
	}
	else if ((protocol == PROTOCOL_POP3) || (protocol == PROTOCOL_APOP)) {
		selected_type_ = TYPE_POP;
		gtk_widget_set_sensitive (get("browse_address"), false);
		identity_view (true);
		details_view (true);
		delay_view (true);
		auth_view (true);
	}
	else if ((protocol == PROTOCOL_IMAP4)) {
		selected_type_ = TYPE_IMAP;
		gtk_widget_set_sensitive (get("browse_address"), false);
		identity_view (true);
		details_view (true);
		delay_view (true);
		mailbox_view (true);
		auth_view (true);
	}

	connection_view (true);

    gtk_combo_box_set_active (GTK_COMBO_BOX (type_cbox_) ,selected_type_);
}
