unity_protocol_scope_service_dbus_interface_method_call (GDBusConnection* connection, const gchar* sender, const gchar* object_path, const gchar* interface_name, const gchar* method_name, GVariant* parameters, GDBusMethodInvocation* invocation, gpointer user_data) {
	gpointer* data;
	gpointer object;
	data = user_data;
	object = data[0];
	if (strcmp (method_name, "Activate") == 0) {
		_dbus_unity_protocol_scope_service_activate (object, parameters, invocation);
	} else if (strcmp (method_name, "Search") == 0) {
		_dbus_unity_protocol_scope_service_search (object, parameters, invocation);
	} else if (strcmp (method_name, "OpenChannel") == 0) {
		_dbus_unity_protocol_scope_service_open_channel (object, parameters, invocation);
	} else if (strcmp (method_name, "CloseChannel") == 0) {
		_dbus_unity_protocol_scope_service_close_channel (object, parameters, invocation);
	} else if (strcmp (method_name, "PushResults") == 0) {
		_dbus_unity_protocol_scope_service_push_results (object, parameters, invocation);
	} else if (strcmp (method_name, "SetViewType") == 0) {
		_dbus_unity_protocol_scope_service_set_view_type (object, parameters, invocation);
	} else {
		g_object_unref (invocation);
	}
}
