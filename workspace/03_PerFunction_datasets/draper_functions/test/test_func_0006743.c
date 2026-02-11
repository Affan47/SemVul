tunnel_complete (SoupConnection *conn, guint status, gpointer user_data)
{
	SoupMessageQueueItem *tunnel_item = user_data;
	SoupMessageQueueItem *item = tunnel_item->related;
	SoupSession *session = tunnel_item->session;

	soup_message_finished (tunnel_item->msg);
	soup_message_queue_item_unref (tunnel_item);

	if (item->msg->status_code)
		item->state = SOUP_MESSAGE_FINISHING;
	soup_message_set_https_status (item->msg, item->conn);

	if (!SOUP_STATUS_IS_SUCCESSFUL (status)) {
		soup_connection_disconnect (conn);
		soup_session_set_item_connection (session, item, NULL);
		soup_session_set_item_status (session, item, status);
	}

	item->state = SOUP_MESSAGE_READY;
	if (item->async)
		soup_session_kick_queue (session);
	soup_message_queue_item_unref (item);
}
