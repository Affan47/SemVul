handle_outgoing_call(DBusMessage *msg)
{
	const char *number, *call_path;
	struct csd_call *call;

	if (!dbus_message_get_args(msg, NULL,
					DBUS_TYPE_OBJECT_PATH, &call_path,
					DBUS_TYPE_STRING, &number,
					DBUS_TYPE_INVALID)) {
		error("Unexpected parameters in Call.Created() signal");
		return;
	}

	call = find_call(call_path);
	if (!call) {
		error("Didn't find any matching call object for %s",
				call_path);
		return;
	}

	DBG("Outgoing call from %s to number %s", call_path, number);

	g_free(call->number);
	call->number = g_strdup(number);

	g_free(last_dialed_number);
	last_dialed_number = g_strdup(number);

	if (create_request_timer) {
		g_source_remove(create_request_timer);
		create_request_timer = 0;
	}
}
