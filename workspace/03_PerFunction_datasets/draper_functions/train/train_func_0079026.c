pk_control_get_time_since_action_cb (GObject *source_object,
				     GAsyncResult *res,
				     gpointer user_data)
{
	GVariant *value;
	GError *error = NULL;
	GDBusProxy *proxy = G_DBUS_PROXY (source_object);
	PkControlState *state = (PkControlState *) user_data;


	value = g_dbus_proxy_call_finish (proxy, res, &error);
	if (value == NULL) {

		pk_control_fixup_dbus_error (error);
		pk_control_get_time_since_action_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	g_variant_get (value, "(u)", &state->time);
	if (state->time == 0) {
		error = g_error_new (PK_CONTROL_ERROR, PK_CONTROL_ERROR_FAILED, "could not get time");
		pk_control_get_time_since_action_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	pk_control_get_time_since_action_state_finish (state, NULL);
out:
	if (value != NULL)
		g_variant_unref (value);
}
