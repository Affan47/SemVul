stub_dbus_bus_remove_match(value bus, value s, value blocking)
{
	CAMLparam3(bus, s, blocking);
	DBusError error;

	dbus_error_init(&error);
	dbus_bus_remove_match(DBusConnection_val(bus), String_val(s),
	                      (Bool_val(blocking) ? &error : NULL));
	if (Bool_val(blocking) && dbus_error_is_set(&error))
		raise_dbus_error(&error);

	CAMLreturn(Val_unit);
}
