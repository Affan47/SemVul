e_ews_connection_add_delegate (EEwsConnection *cnc,
                               gint pri,
                               const gchar *mail_id,
                               const GSList *delegates,
                               GCancellable *cancellable,
                               GAsyncReadyCallback callback,
                               gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;
	const GSList *iter;

	g_return_if_fail (cnc != NULL);
	g_return_if_fail (delegates != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"AddDelegate",
			NULL,
			NULL,
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE);

	e_soap_message_start_element (msg, "Mailbox", "messages", NULL);
	e_ews_message_write_string_parameter (msg, "EmailAddress", NULL, mail_id ? mail_id : cnc->priv->email);
	e_soap_message_end_element (msg);

	e_soap_message_start_element (msg, "DelegateUsers", "messages", NULL);
	for (iter = delegates; iter; iter = iter->next) {
		const EwsDelegateInfo *di = iter->data;

		if (!di)
			continue;

		e_soap_message_start_element (msg, "DelegateUser", NULL, NULL);

		e_soap_message_start_element (msg, "UserId", NULL, NULL);
		e_ews_message_write_string_parameter (msg, "PrimarySmtpAddress", NULL, di->user_id->primary_smtp);
		e_soap_message_end_element (msg);

		e_soap_message_start_element (msg, "DelegatePermissions", NULL, NULL);
		set_delegate_permission (msg, "CalendarFolderPermissionLevel", di->calendar);
		set_delegate_permission (msg, "TasksFolderPermissionLevel", di->tasks);
		set_delegate_permission (msg, "InboxFolderPermissionLevel", di->inbox);
		set_delegate_permission (msg, "ContactsFolderPermissionLevel", di->contacts);
		set_delegate_permission (msg, "NotesFolderPermissionLevel", di->notes);
		set_delegate_permission (msg, "JournalFolderPermissionLevel", di->journal);
		e_soap_message_end_element (msg);

		e_ews_message_write_string_parameter (
			msg, "ReceiveCopiesOfMeetingMessages", NULL,
			di->meetingcopies ? "true" : "false");
		e_ews_message_write_string_parameter (
			msg, "ViewPrivateItems", NULL,
			di->view_priv_items ? "true" : "false");

		e_soap_message_end_element (msg);
	}

	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_add_delegate);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, update_delegate_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}
