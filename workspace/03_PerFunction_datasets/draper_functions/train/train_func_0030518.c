dvb_id_bus_schedule_dbus_interface_method_call (GDBusConnection* connection, const gchar* sender, const gchar* object_path, const gchar* interface_name, const gchar* method_name, GVariant* parameters, GDBusMethodInvocation* invocation, gpointer user_data) {
	gpointer* data;
	gpointer object;
	data = user_data;
	object = data[0];
	if (strcmp (method_name, "GetAllEvents") == 0) {
		_dbus_dvb_id_bus_schedule_GetAllEvents (object, parameters, invocation);
	} else if (strcmp (method_name, "GetAllEventInfos") == 0) {
		_dbus_dvb_id_bus_schedule_GetAllEventInfos (object, parameters, invocation);
	} else if (strcmp (method_name, "GetInformations") == 0) {
		_dbus_dvb_id_bus_schedule_GetInformations (object, parameters, invocation);
	} else if (strcmp (method_name, "NowPlaying") == 0) {
		_dbus_dvb_id_bus_schedule_NowPlaying (object, parameters, invocation);
	} else if (strcmp (method_name, "Next") == 0) {
		_dbus_dvb_id_bus_schedule_Next (object, parameters, invocation);
	} else if (strcmp (method_name, "GetName") == 0) {
		_dbus_dvb_id_bus_schedule_GetName (object, parameters, invocation);
	} else if (strcmp (method_name, "GetShortDescription") == 0) {
		_dbus_dvb_id_bus_schedule_GetShortDescription (object, parameters, invocation);
	} else if (strcmp (method_name, "GetExtendedDescription") == 0) {
		_dbus_dvb_id_bus_schedule_GetExtendedDescription (object, parameters, invocation);
	} else if (strcmp (method_name, "GetDuration") == 0) {
		_dbus_dvb_id_bus_schedule_GetDuration (object, parameters, invocation);
	} else if (strcmp (method_name, "GetLocalStartTime") == 0) {
		_dbus_dvb_id_bus_schedule_GetLocalStartTime (object, parameters, invocation);
	} else if (strcmp (method_name, "GetLocalStartTimestamp") == 0) {
		_dbus_dvb_id_bus_schedule_GetLocalStartTimestamp (object, parameters, invocation);
	} else if (strcmp (method_name, "IsRunning") == 0) {
		_dbus_dvb_id_bus_schedule_IsRunning (object, parameters, invocation);
	} else if (strcmp (method_name, "IsScrambled") == 0) {
		_dbus_dvb_id_bus_schedule_IsScrambled (object, parameters, invocation);
	} else {
		g_object_unref (invocation);
	}
}
