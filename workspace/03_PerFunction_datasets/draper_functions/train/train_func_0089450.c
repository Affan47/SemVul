handle_method_call_pause (TrackerMiner          *miner,
                          GDBusMethodInvocation *invocation,
                          GVariant              *parameters)
{
	GError *local_error = NULL;
	gint cookie;
	const gchar *application = NULL, *reason = NULL;
	TrackerDBusRequest *request;

	g_variant_get (parameters, "(&s&s)", &application, &reason);

	tracker_gdbus_async_return_if_fail (application != NULL, invocation);
	tracker_gdbus_async_return_if_fail (reason != NULL, invocation);

	request = tracker_g_dbus_request_begin (invocation,
	                                        "%s(application:'%s', reason:'%s')",
	                                        __PRETTY_FUNCTION__,
	                                        application,
	                                        reason);

	cookie = miner_pause_internal (miner, application, reason, NULL, &local_error);
	if (cookie == -1) {
		tracker_dbus_request_end (request, local_error);

		g_dbus_method_invocation_return_gerror (invocation, local_error);

		g_error_free (local_error);

		return;
	}

	tracker_dbus_request_end (request, NULL);
	g_dbus_method_invocation_return_value (invocation,
	                                       g_variant_new ("(i)", cookie));
}
