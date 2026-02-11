pk_control_set_proxy_cb (GObject *source_object,
				   GAsyncResult *res,
				   gpointer user_data)
{
	GError *error = NULL;
	GVariant *value;
	GDBusProxy *proxy = G_DBUS_PROXY (source_object);
	PkControlState *state = (PkControlState *) user_data;


	value = g_dbus_proxy_call_finish (proxy, res, &error);
	if (value == NULL) {
		g_warning ("failed to set proxy: %s", error->message);
		pk_control_set_proxy_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	state->ret = TRUE;


	pk_control_set_proxy_state_finish (state, NULL);
out:
	if (value != NULL)
		g_variant_unref (value);
}
