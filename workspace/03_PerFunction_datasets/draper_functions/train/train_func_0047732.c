pk_client_get_tid_cb (GObject *object, GAsyncResult *res, PkClientState *state)
{
	GError *error = NULL;
	PkControl *control = PK_CONTROL (object);

	state->tid = pk_control_get_tid_finish (control, res, &error);
	if (state->tid == NULL) {
		pk_client_state_finish (state, error);
		g_error_free (error);
		return;
	}

	pk_progress_set_transaction_id (state->progress, state->tid);


	g_dbus_proxy_new_for_bus (G_BUS_TYPE_SYSTEM,
				  G_DBUS_PROXY_FLAGS_NONE,
				  NULL,
				  PK_DBUS_SERVICE,
				  state->tid,
				  PK_DBUS_INTERFACE_TRANSACTION,
				  state->cancellable,
				  pk_client_get_proxy_cb,
				  state);
}
