handle_method_call (GDBusConnection *connection,
		    const char *sender,
		    const char *object_path,
		    const char *interface_name,
		    const char *method_name,
		    GVariant *parameters,
		    GDBusMethodInvocation *invocation,
		    ServiceData *svc)
{
	rb_debug ("handling metadata service message: %s.%s", interface_name, method_name);
	if (g_strcmp0 (method_name, "ping") == 0) {
		rb_metadata_dbus_ping (parameters, invocation, svc);
	} else if (g_strcmp0 (method_name, "load") == 0) {
		rb_metadata_dbus_load (parameters, invocation, svc);
	} else if (g_strcmp0 (method_name, "getSaveableTypes") == 0) {
		rb_metadata_dbus_get_saveable_types (parameters, invocation, svc);
	} else if (g_strcmp0 (method_name, "save") == 0) {
		rb_metadata_dbus_save (parameters, invocation, svc);
	}
	svc->last_active = time (NULL);
}
