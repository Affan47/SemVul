cal_client_emit_backend_error_idle_cb (gpointer user_data)
{
	SignalClosure *signal_closure = user_data;
	EClient *client;

	client = g_weak_ref_get (&signal_closure->client);

	if (client != NULL) {
		g_signal_emit_by_name (
			client, "backend-error",
			signal_closure->error_message);
		g_object_unref (client);
	}

	return FALSE;
}
