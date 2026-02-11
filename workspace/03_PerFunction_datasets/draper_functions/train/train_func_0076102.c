scan_callback(DBusPendingCall *pending, void *user_data)
{
	struct connman_technology *technology = user_data;

	if (dbus_pending_call_get_completed(pending) == FALSE)
		return;

	dbus_pending_call_unref(pending);
	technology->scan_call = NULL;

	if (technology->scan_cb != NULL)
		technology->scan_cb(technology->scan_user_data);
}
