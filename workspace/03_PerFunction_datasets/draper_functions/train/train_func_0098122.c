item_get_info_2_reply (GkrOperation *op, GkrSession *session, gpointer data)
{
	item_get_info_args *args = data;
	const char *path;
	DBusMessage *req;

	g_assert (!args->session);
	args->session = gkr_session_ref (session);

	req = dbus_message_new_method_call (gkr_service_name, args->path, ITEM_INTERFACE, "GetSecret");
	path = gkr_session_get_path (session);
	dbus_message_append_args (req, DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID);

	gkr_operation_push (op, item_get_info_3_reply, GKR_CALLBACK_OP_MSG, args, NULL);
	gkr_operation_request (op, req);
	dbus_message_unref (req);
}
