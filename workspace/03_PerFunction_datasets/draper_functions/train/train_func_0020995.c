auth_cb(DBusError *derr, void *user_data)
{
	struct service_adapter *serv_adapter = user_data;
	DBusMessage *reply;
	struct pending_auth *auth;
	bdaddr_t src;

	auth = next_pending(serv_adapter);
	if (auth == NULL) {
		info("Authorization cancelled: Client exited");
		return;
	}

	if (derr) {
		error("Access denied: %s", derr->message);

		reply = btd_error_not_authorized(auth->msg);
		dbus_message_unref(auth->msg);
		g_dbus_send_message(auth->conn, reply);
		goto done;
	}

	g_dbus_send_reply(auth->conn, auth->msg,
			DBUS_TYPE_INVALID);

done:
	dbus_connection_unref(auth->conn);

	serv_adapter->pending_list = g_slist_remove(serv_adapter->pending_list,
									auth);
	g_free(auth);

	auth = next_pending(serv_adapter);
	if (auth == NULL)
		return;

	if (serv_adapter->adapter)
		adapter_get_address(serv_adapter->adapter, &src);
	else
		bacpy(&src, BDADDR_ANY);

	btd_request_authorization(&src, &auth->dst,
					auth->uuid, auth_cb, serv_adapter);
}
