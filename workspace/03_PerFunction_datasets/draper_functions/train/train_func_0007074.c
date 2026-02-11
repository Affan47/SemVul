secure_to_port_cb (GBinding *binding,
                   const GValue *source_value,
                   GValue *target_value,
                   gpointer user_data)
{
	GObject *authentication_extension;
	guint16 port;

	authentication_extension = g_binding_get_target (binding);

	port = e_source_authentication_get_port (
		E_SOURCE_AUTHENTICATION (authentication_extension));

	if (port == 80 || port == 443 || port == 0)
		port = g_value_get_boolean (source_value) ? 443 : 80;

	g_value_set_uint (target_value, port);

	return TRUE;
}
