g_dbus_pending_success(DBusConnection *connection,
					GDBusPendingReply pending)
{
	GSList *list;

	for (list = pending_security; list; list = list->next) {
		struct security_data *secdata = list->data;

		if (secdata->pending != pending)
			continue;

		pending_security = g_slist_remove(pending_security, secdata);

		process_message(connection, secdata->message,
				secdata->method, secdata->iface_user_data);

		dbus_message_unref(secdata->message);
		g_free(secdata);
		return;
	}
}
