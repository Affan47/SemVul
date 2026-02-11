ForwardSMS(void)
{
	gchar *buf;
	GtkTextBuffer *buffer;

	if (GTK_CLIST(SMS.smsClist)->selection == NULL)
		return;

	if (!sendSMS.SMSSendWindow)
		CreateSMSSendWindow();

	gtk_window_set_title(GTK_WINDOW(sendSMS.SMSSendWindow), _("Forward Message"));

	gtk_tooltips_disable(sendSMS.addrTip);

	gtk_clist_get_text(GTK_CLIST(SMS.smsClist),
			   GPOINTER_TO_INT(GTK_CLIST(SMS.smsClist)->selection->data), 3, &buf);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(sendSMS.smsSendText));
	gtk_text_buffer_set_text(buffer, buf, -1);

	gtk_entry_set_text(GTK_ENTRY(sendSMS.addr), "");

	RefreshSMSStatus();

	gtk_window_present(GTK_WINDOW(sendSMS.SMSSendWindow));
}
