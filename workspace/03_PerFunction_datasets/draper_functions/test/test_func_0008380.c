handle_method_call_resume (TrackerMiner          *miner,
                           GDBusMethodInvocation *invocation,
                           GVariant              *parameters)
{
	GError *local_error = NULL;
	gint cookie;
	TrackerDBusRequest *request;

	g_variant_get (parameters, "(i)", &cookie);

	request = tracker_g_dbus_request_begin (invocation,
	                                        "%s(cookie:%d)",
	                                        __PRETTY_FUNCTION__,
	                                        cookie);

	if (!tracker_miner_resume (miner, cookie, &local_error)) {
		tracker_dbus_request_end (request, local_error);

		g_dbus_method_invocation_return_gerror (invocation, local_error);

		g_error_free (local_error);
		return;
	}

	tracker_dbus_request_end (request, NULL);
	g_dbus_method_invocation_return_value (invocation, NULL);
}
