e_ews_connection_delete_items (EEwsConnection *cnc,
                               gint pri,
                               GSList *ids,
                               EwsDeleteType delete_type,
                               EwsSendMeetingCancellationsType send_cancels,
                               EwsAffectedTaskOccurrencesType affected_tasks,
                               GCancellable *cancellable,
                               GAsyncReadyCallback callback,
                               gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;
	GSList *l;

	g_return_if_fail (cnc != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"DeleteItem",
			"DeleteType",
			ews_delete_type_to_str (delete_type),
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE);

	if (send_cancels)
		e_soap_message_add_attribute (
			msg, "SendMeetingCancellations",
			ews_send_cancels_to_str (send_cancels), NULL, NULL);

	if (affected_tasks)
		e_soap_message_add_attribute (
			msg, "AffectedTaskOccurrences",
			ews_affected_tasks_to_str (affected_tasks), NULL, NULL);

	e_soap_message_start_element (msg, "ItemIds", "messages", NULL);

	for (l = ids; l != NULL; l = g_slist_next (l))
		e_ews_message_write_string_parameter_with_attribute (msg, "ItemId", NULL, NULL, "Id", l->data);

	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_delete_items);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, delete_item_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}
